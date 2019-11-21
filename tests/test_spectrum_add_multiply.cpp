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
    static std::uniform_int_distribution<> dis(0, 7);

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
    std::cout << "A" << std::endl;
    std::vector<double> a(16);
    std::generate(a.begin(), a.end(), test_generator);
    core::optics::Spectrum sA(a);
    print_spectrum(sA);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << sA.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "B" << std::endl;
    std::vector<double> b(3, 2.0);
    core::optics::Spectrum sB(b);
    print_spectrum(sB);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << sB.integral() << std::endl;
    std::cout << std::endl;


    std::cout << "A.add(B), A:" << std::endl;
    std::cout << "Note integrals are not perfectly added, cause there was an upscale for B up to A.size" << std::endl;
    std::cout << "When scaling integral is changing slightly, even when it is y = const, " << std::endl;
    std::cout << "cause of interpolation near boundaries - outside of them value is 0.0" << std::endl;
    sA.add(sB);
    print_spectrum(sA);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << sA.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "C" << std::endl;
    std::vector<double> c{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    core::optics::Spectrum sC(c);
    print_spectrum(sC);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << sC.integral() << std::endl;
    std::cout << std::endl;

    std::cout << "A.multiply(C), A:" << std::endl;
    sA.multiply(sC);
    print_spectrum(sA);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << sA.integral() << std::endl;
    std::cout << std::endl;


    return 0;
}
