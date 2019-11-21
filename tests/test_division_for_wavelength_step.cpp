#include <iostream>
//#include "src/core/geometry.h"
#include <random>
#include <iomanip>

int main()
{


    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 256);


    int i = 1000;
    double a = 740.0 - 380.0;
    double b, c;
    while(i)
    {
        b = dis(gen);

        c = a/b;

        if((c*b) > a)
        {
            std::cout << std::setprecision(16) << "a   " << a << std::endl;
            std::cout << std::setprecision(16) << "b   " << b << std::endl;
            std::cout << std::setprecision(16) << "c   " << c << std::endl;
            std::cout << std::setprecision(16) << "c*b " << c*b << std::endl;
            std::cout << std::endl;


        }
        --i;
    }

  return 0;
}
