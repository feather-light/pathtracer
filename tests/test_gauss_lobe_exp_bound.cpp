#include <iostream>
// #include "src/core/optics/spectrum.h"
// #include <algorithm>
// #include <random>
// #include <vector>
// #include <string>
#include <iomanip>

#define _USE_MATH_DEFINES
#include <cmath>
int main()
{
    double angle_max{M_PI_2};
    double exp_min_arg{-708.4};
    double spread_max_by_exp{angle_max/std::sqrt(-exp_min_arg)};



    std::cout << std::fixed << std::setprecision(15) << spread_max_by_exp << std::endl;

    double t{angle_max/spread_max_by_exp};
    std::cout << std::fixed << std::setprecision(15) << t*t << " < 708.4" << std::endl;


    return 0;
}
