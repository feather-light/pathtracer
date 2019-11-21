#include <iostream>
#include "src/core/optics/spectrum.h"
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

double test_generator()
{
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_int_distribution<> dis(0, 9);

    return dis(gen);
}

void print_spectrum(const core::optics::Spectrum& s)
{
    auto ws{s.wavelengths()};
    double intens{0.0};
    for(const auto& w: ws)
    {
        intens = s.value_interpolated(w);
        //std::cout << std::fixed << std::setprecision(5) << w << "|" << intens << "|" << std::string( int(intens), '*') << std::endl;
        std::cout << std::fixed << std::setprecision(15) << w << "|" << intens << "|" << std::string( int(std::round(intens)), '*') << std::endl;
    }
}

int main()
{
    std::cout << "Original" << std::endl;
    std::vector<double> a(16);
    std::generate(a.begin(), a.end(), test_generator);
    core::optics::Spectrum s(a);
    print_spectrum(s);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "Interpolation for doubled number of wavelengths" << std::endl;
    std::vector<double> b(32);
    auto ws = core::optics::Spectrum(b).wavelengths();
    double intens{0.0};
    for(const auto& w: ws)
    {
        intens = s.value_interpolated(w);
        //std::cout << std::fixed << std::setprecision(5) << w << "|" << intens << "|" << std::string( int(intens), '*') << std::endl;
        std::cout << std::fixed << std::setprecision(15) << w << "|" << intens << "|" << std::string( int(std::round(intens)), '*') << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Scaled up by 2" << std::endl;
    core::optics::Spectrum s_scaled_up(s, 32);
    print_spectrum(s_scaled_up);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s_scaled_up.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "Scaled down by 2" << std::endl;
    core::optics::Spectrum s_scaled_down(s, 8);
    print_spectrum(s_scaled_down);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s_scaled_down.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "Constructor of table + size for loading from files" << std::endl;
    std::cout << "Should be exactly like scaled up by 2" << std::endl;
    core::optics::Spectrum s_load(a, 32);
    print_spectrum(s_load);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s_load.integral() << std::endl;



    return 0;
}
