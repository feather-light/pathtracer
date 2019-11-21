#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

#include "src/custom/render/topngsaver.h"

void print_spectrum(const core::optics::Spectrum& s)
{
    auto ws{s.wavelengths()};
    double intens{0.0};
    for(const auto& w: ws)
    {
        intens = s.value_interpolated(w);
        intens*=50;
        //std::cout << std::fixed << std::setprecision(5) << w << "|" << intens << "|" << std::string( int(intens), '*') << std::endl;
        std::cout << std::fixed << std::setprecision(15) << w << "|" << intens << "|" << std::string( int(std::round(intens)), '*') << std::endl;
    }
}

int main()
{
    custom::render::ToPNGSaver saver{64};
    const auto& [x, y, z] {saver.check()};


    std::cout << "X" << std::endl;
    print_spectrum(x);
    std::cout << std::fixed << std::setprecision(16) << "Integral: " << x.integral() << std::endl;
    std::cout << std::endl;


    std::cout << "Y" << std::endl;
    print_spectrum(y);
    std::cout << std::fixed << std::setprecision(16) << "Integral: " << y.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "Z" << std::endl;
    print_spectrum(z);
    std::cout << std::fixed << std::setprecision(16) << "Integral: " << z.integral() << std::endl;
    std::cout << std::endl;

    return 0;
}
