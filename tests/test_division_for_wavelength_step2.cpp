#include <iostream>
//#include "src/core/geometry.h"
#include <random>
#include <iomanip>

int main()
{


    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 256);
    std::uniform_real_distribution<> fdis(740.0, 740.0);

    int i = 10;
    double min = 380.0;
    int n;
    double s, w;
    while(i)
    {
        n = dis(gen);

        s = (740.0-380)/n;

        w = fdis(gen);

       // if( int((w - min)/s) >= n )
        {
            std::cout << std::setprecision(16) << "n   " << n << std::endl;
            std::cout << std::setprecision(16) << "s   " << s << std::endl;
            std::cout << std::setprecision(16) << "w   " << w << std::endl;
            std::cout << std::setprecision(16) << "interv " << int((w - min)/s) << std::endl;
            std::cout << std::endl;


        }
        --i;
    }

  return 0;
}
