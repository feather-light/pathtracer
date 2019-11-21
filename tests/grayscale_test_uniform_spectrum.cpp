#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

#include "src/custom/render/singlesimpletile.h"
#include "src/custom/render/topngsaver.h"

// void print_spectrum(const core::optics::Spectrum& s)
// {
//     auto ws{s.wavelengths()};
//     double intens{0.0};
//     for(const auto& w: ws)
//     {
//         intens = s.value_interpolated(w);
//         intens*=10;
//         //std::cout << std::fixed << std::setprecision(5) << w << "|" << intens << "|" << std::string( int(intens), '*') << std::endl;
//         std::cout << std::fixed << std::setprecision(15) << w << "|" << intens << "|" << std::string( int(std::round(intens)), '*') << std::endl;
//     }
// }

int main()
{
    const int width{256};
    custom::render::SingleSimpleTile tile {width, 1, 32};
    for(int intens = 0; intens < width; ++intens)
    {
        tile.pixel(intens, 0, { {double(intens), double(intens)} } );
    }

    custom::render::ToPNGSaver saver {64};
    saver.save(tile, "img/grayscale_test_uniform_spectrum.png");

    return 0;
}
