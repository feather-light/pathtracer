#include "topngsaver.h"

#include <pngwriter.h>

#include <cmath>
#include <vector>
#include <algorithm>

namespace custom::render
{
    ToPNGSaver::ToPNGSaver(std::size_t spectrum_table_size) :
        XYZ_m { [spectrum_table_size]() mutable -> std::map<std::string, core::optics::Spectrum>
                {
                    // spectrum should contain at least 2 elements
                    spectrum_table_size = (spectrum_table_size < 2) ? 2 : spectrum_table_size;

                    // just to get wavelengths
                    const core::optics::Spectrum stmp{ {0.0, 0.0}, spectrum_table_size};

                    // creating tables for X Y Z spectrum functions
                    const auto ws{stmp.wavelengths()};
                    std::vector<double> x;
                    std::vector<double> y;
                    std::vector<double> z;
                    for(const auto w : ws)
                    {
                        x.push_back( xf_XYZ(w) );
                        y.push_back( yf_XYZ(w) );
                        z.push_back( zf_XYZ(w) );
                    }

                    // representing as a map
                    return { {"X", {x} },
                             {"Y", {y} },
                             {"Z", {z} } };
                }()
              } {}


    void ToPNGSaver::save (const core::render::IImageTile& image, std::string filename) const
    {
        using namespace core::geometry;

        // getting size
        const auto [x_min, y_min, x_max, y_max] {image.bounds()};
        const auto width{x_max - x_min + 1};
        const auto height{y_max - y_min + 1};

        // image in XYZ colour space, pitch black by default
        std::vector< std::vector <Vector> > image_XYZ (width, std::vector <Vector>(height, {0.0, 0.0, 0.0} ) );

        const std::size_t spectrum_table_size{XYZ_m.at("X").table_size()};

        for(int x = 0; x < width; ++x )
        {
            for(int y = 0; y < height; ++y )
            {
                // spectrum copy with adjusted table size
                core::optics::Spectrum s_x { image.pixel(x, y).value(), spectrum_table_size };
                auto s_y { s_x };
                auto s_z { s_x };

                // getting spectral image for X channel
                s_x.multiply(XYZ_m.at("X"));
                image_XYZ[x][y].x = s_x.integral();

                s_y.multiply(XYZ_m.at("Y"));
                image_XYZ[x][y].y = s_y.integral();

                s_z.multiply(XYZ_m.at("Z"));
                image_XYZ[x][y].z = s_z.integral();
            }
        }

        // to adjust intensity we should find maximum of Y component,
        // since it represents maximum power in colour model
        double max_y{0.0};
        for(const auto& column : image_XYZ)
        {
            for(const auto& pixel_XYZ : column)
            {
                max_y = std::max(max_y, pixel_XYZ.y);
            }
        }

        if(max_y > 0.0)
        {
            // since Y should be 1 at the brightest point
            // and it is reference in colour model
            // we should normalize all pixel in reference to the maximum
            const double max_y_inv{1.0/max_y};
            for(auto& column : image_XYZ)
            {
                for(auto& pixel_XYZ : column)
                {
                    pixel_XYZ.scale(max_y_inv);
                }
            }
        }

        //creating final png image
        pngwriter image_png {width, height, 0.0, filename.c_str()};
        double r;
        double g;
        double b;
        for(int x = 0; x < width; ++x )
        {
            for(int y = 0; y < height; ++y )
            {
                // matrix transformation from XYZ colour space to sRGB
                const auto& pixel_XYZ {image_XYZ[x][y]};
                r = scalar_product(pixel_XYZ, M_XYZ_to_RGB_s.at("R"));
                g = scalar_product(pixel_XYZ, M_XYZ_to_RGB_s.at("G"));
                b = scalar_product(pixel_XYZ, M_XYZ_to_RGB_s.at("B"));

                // since there are colours in XYZ, that could not be represented in sRGB
                // components might be under and over [0.0, 1.0]
                // those colours should be rounded to the bounds
                r = std::max(0.0, std::min(1.0, r));
                g = std::max(0.0, std::min(1.0, g));
                b = std::max(0.0, std::min(1.0, b));

                // +1 is because of origin point is (1, 1)
                image_png.plot(x+1, y+1, r, g, b);
            }
        }

        image_png.close();
    }



    // those are analytical representations of spectral functions X Y Z
    // they are correspond to CIE 1931 standard observer

    // since wavelength belongs to [380.0, 740.0]
    // across all functions exp arguments belong to [0.0, -113.738]
    // so std::exp is safe to use
    double ToPNGSaver::xf_XYZ(double wavelength)
    {
        const double t1{ (wavelength - 595.8)/33.33 };
        const double t2{ (wavelength - 446.8)/19.44 };

        return ( 1.065*std::exp((-0.5)*(t1*t1)) + 0.366*std::exp((-0.5)*(t2*t2)) );
    }

    double ToPNGSaver::yf_XYZ(double wavelength)
    {
        const double t{ ( std::log(wavelength) - std::log(556.3) )/0.075 };

        return 1.014*std::exp((-0.5)*(t*t));
    }

    double ToPNGSaver::zf_XYZ(double wavelength)
    {
        const double t{ ( std::log(wavelength) - std::log(449.8) )/0.051 };

        return 1.839*std::exp((-0.5)*(t*t));
    }

}
