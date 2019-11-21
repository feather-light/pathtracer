#include <iostream>
#include "src/core/optics/laws.h"
// #include <algorithm>
 #include <random>
// #include <vector>
// #include <string>
#include <iomanip>

#define _USE_MATH_DEFINES
#include <cmath>
int main()
{
    static std::random_device rd1;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen1(rd1()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> dis1(0.0, M_PI_2);

    static std::random_device rd2;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen2(rd2()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> dis2(0.00001, 1.0);

    int i{10};
    double angle{};
    double spread{};
    double intens{};
    while(i)
    {
        angle = dis1(gen1);
        spread = dis2(gen2);
        intens = core::optics::gaussian_petal(angle, spread);

        //if(intens > 1.0) //to check if there is err, tested to be ok
        if(intens <= 1.0)
        {
            std::cout << std::fixed << std::setprecision(15) << "angle (grad): " << 180.0 * angle/M_PI << std::endl;
            std::cout << std::fixed << std::setprecision(15) << "spread: " << spread << std::endl;
            std::cout << std::fixed << std::setprecision(15) << "intens: " << intens << std::endl;
            std::cout << std::endl;
        }

        --i;
    }

    std::cout << "Done" << std::endl;

    return 0;
}
