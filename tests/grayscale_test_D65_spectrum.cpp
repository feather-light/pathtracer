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
    const core::optics::Spectrum D65 {{
    49.975500,
    52.311800,
    54.648200,
    68.701500,
    82.754900,
    87.120400,
    91.486000,
    92.458900,
    93.431800,
    90.057000,
    86.682300,
    95.773600,
    104.865000,
    110.936000,
    117.008000,
    117.410000,
    117.812000,
    116.336000,
    114.861000,
    115.392000,
    115.923000,
    112.367000,
    108.811000,
    109.082000,
    109.354000,
    108.578000,
    107.802000,
    106.296000,
    104.790000,
    106.239000,
    107.689000,
    106.047000,
    104.405000,
    104.225000,
    104.046000,
    102.023000,
    100.000000,
    98.167100,
    96.334200,
    96.061100,
    95.788000,
    92.236800,
    88.685600,
    89.345900,
    90.006200,
    89.802600,
    89.599100,
    88.648900,
    87.698700,
    85.493600,
    83.288600,
    83.493900,
    83.699200,
    81.863000,
    80.026800,
    80.120700,
    80.214600,
    81.246200,
    82.277800,
    80.281000,
    78.284200,
    74.002700,
    69.721300,
    70.665200,
    71.609100,
    72.979000,
    74.349000,
    67.976500,
    61.604000,
    65.744800,
    69.885600,
    72.486300,
    75.087000
    }};

    const int width{256};
    custom::render::SingleSimpleTile tile {width, 1, 32};
    for(int intens = 0; intens < width; ++intens)
    {
        auto s{D65};
        s.scale(intens);
        tile.pixel(intens, 0, s);
    }

    custom::render::ToPNGSaver saver {64};
    saver.save(tile, "img/grayscale_test_D65_spectrum.png");

    return 0;
}
