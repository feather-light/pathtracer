/*
 * ToPNGSaver implements IImageSaver interface.
 * It allows to save spectral images in png format.
 * This is achieved through the process of transformation of an image into
 * XYZ colour space, which is then converted to RGB colour model representation.
 * To work with png files it uses external library by the name of pngwriter.
 *
 */

#pragma once

#include "../../core.h"

#include <map>
#include <string>

namespace custom::render
{
    class ToPNGSaver : public core::render::IImageSaver
    {
    public:
        ToPNGSaver(std::size_t spectrum_table_size);

        virtual void save (const core::render::IImageTile& image, std::string filename) const override;

    private:
        // matrix from XYZ to RGB
        // target colour space is sRGB with reference white point D65
        static inline const std::map<std::string, core::geometry::Vector> M_XYZ_to_RGB_s { {"R", { 3.2404542, -1.5371385, -0.4985314} },
                                                                                           {"G", {-0.9692660,  1.8760108,  0.0415560} },
                                                                                           {"B", { 0.0556434, -0.2040259,  1.0572252} } };

        std::map<std::string, core::optics::Spectrum> XYZ_m;

        static double xf_XYZ(double wavelength);
        static double yf_XYZ(double wavelength);
        static double zf_XYZ(double wavelength);

    };
}
