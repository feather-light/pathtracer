#include "singlesimpletile.h"

namespace custom::render
{
    SingleSimpleTile::SingleSimpleTile(int width, int height, std::size_t spectrum_res) :
        image_m{ [&width, &height, &spectrum_res]() -> std::vector< std::vector<core::optics::Spectrum> >
               {
                   width = (width < 1) ? 1 : width;
                   height = (height < 1) ? 1 : height;
                   spectrum_res = (spectrum_res < 2) ? 2 : spectrum_res;

                   return std::vector< std::vector<core::optics::Spectrum> >(width, std::vector<core::optics::Spectrum>(height, core::optics::Spectrum{ {0.0, 0.0}, spectrum_res }) );
               }()
             },
         current_x_m{0},
         current_y_m{0} {}


    std::optional<std::pair <int, int>> SingleSimpleTile::next_pixel() const
    {
        // this one is sequential, pixels are returned in increasing order
        const int width{ int(image_m.size()) };
        const int height{ int(image_m[0].size()) };

        // means we have reached the end
        if (current_x_m == width)
        {
            return std::nullopt;
        }

        int x{current_x_m};
        int y{current_y_m};

        current_y_m++;
        if(current_y_m == height)
        {
            current_y_m = 0;
            current_x_m++;
        }

        return {{x, y}};
    }

    void SingleSimpleTile::reset()
    {
        current_x_m = 0;
        current_y_m = 0;
    }

    std::optional<core::optics::Spectrum> SingleSimpleTile::pixel(int x, int y) const
    {
        const int width{ int(image_m.size()) };
        const int height{ int(image_m[0].size()) };

        if( (x < 0) || (width <= x) )
        {
            return std::nullopt;
        }

        if( (y < 0) || (height <= y) )
        {
            return std::nullopt;
        }

        return image_m[x][y];
    }

    void SingleSimpleTile::pixel(int x, int y, const core::optics::Spectrum& spectrum)
    {
        const int width{ int(image_m.size()) };
        const int height{ int(image_m[0].size()) };

        if( (x < 0) || (width <= x) )
        {
            return;
        }

        if( (y < 0) || (height <= y) )
        {
            return;
        }

        // since it is a direct assignment
        // we need to ensure table size is correct
        if(spectrum.table_size() != spectrum_table_size())
        {
            image_m[x][y] = {spectrum, spectrum_table_size()};
        }
        else
        {
            image_m[x][y] = spectrum;
        }

    }

    std::tuple<int, int, int, int> SingleSimpleTile::bounds() const
    {
        const int width{ int(image_m.size()) };
        const int height{ int(image_m[0].size()) };

        return {0, 0, width-1, height-1};
    }

    std::size_t SingleSimpleTile::spectrum_table_size() const
    {
        return image_m[0][0].table_size();
    }
}
