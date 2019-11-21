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
    std::vector<double> a(16);
    std::generate(a.begin(), a.end(), test_generator);
    core::optics::Spectrum s1(a);
    print_spectrum(s1);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s1.integral() << std::endl;

    std::cout << std::endl;

    //note how there appears little err when interpolating on table with not suitable step - it is totally fine
    std::vector<double> b(20);
    std::generate(b.begin(), b.end(), test_generator);
    core::optics::Spectrum s2(b);
    print_spectrum(s2);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s2.integral() << std::endl;

    std::cout << std::endl;

    // integral check, should be 4.0*(740-380) = 1440
    std::vector<double> c(9, 4.0);
    core::optics::Spectrum s3(c);
    print_spectrum(s3);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s3.integral() << std::endl;

    std::cout << std::endl;

    //now test for scale, should be 10, integral 3600
    s3.scale(2.5);
    print_spectrum(s3);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s3.integral() << std::endl;

    std::cout << std::endl;

    //normalizing
    s3.normalize();
    print_spectrum(s3);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s3.integral() << std::endl;

    std::cout << std::endl;

    //another (with random) normalizing
    s2.normalize();
    print_spectrum(s2);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s2.integral() << std::endl;

    std::cout << std::endl;

    // at last, is 32 a good number of samples, to represent color precisely enough?
    std::vector<double> d(32);
    std::generate(d.begin(), d.end(), test_generator);
    core::optics::Spectrum s4(d);
    print_spectrum(s4);
    std::cout << std::fixed << std::setprecision(3) << "Integral: " << s4.integral() << std::endl;

    return 0;
}
