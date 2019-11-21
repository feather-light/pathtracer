#include "laws.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>

namespace core::optics
{
    // designed to take angle  [-M_PI_2, M_PI_2] as for petal, other input results in 0.0
    //                  spread [0.00001, 1.0]
    // return value belongs to [0.0, 1.0]
    // e^((-0.5)*(angle/spread)^2)
    double gaussian_petal(double angle, double spread)
    {
        if(std::abs(angle) > M_PI_2)
        {
            return 0.0;
        }

        // maybe it is better to throw exception in this case, but it is how it goes for now
        // too bad contracts in C++ are not available yet
        if( (spread < 0.00001) || (1.0 < spread) )
        {
            return 0.0;
        }

        // [0.00001, 1.0] range is normalized to 1.0 for the ease of use
        // gaussian function needs spread of [0.0001, 10] to work as intended
        spread*=10.0;

        if(spread >= 0.05)
        {
            // std::exp(double) from <cmath>, according to documentation, takes arguments in range:
            // "For IEEE-compatible type double, overflow is guaranteed if 709.8 < arg, and underflow is guaranteed if arg < -708.4."
            // upper limit is not interesting to us, since we are using only negative values as an argument, lower limit is crucial thou.
            // For that matter, we need to find out what minimal spread can exp handle
            // (-0.5)*(angle/spread)^2 > -708.4
            // angle should be assumed maximum, so
            // (M_PI_2/spread)^2 < 708.4*2.0
            // M_PI_2/sqrt(708.4*2.0) < spread
            // 0.041731654478480 < spread
            // so, we can use exp only when spread is over 0.041731654478480
            // to avoid any possible near-overflow precision err and to play it simple, we are setting bar at 0.05

            const double t{angle/spread};
            return std::exp((-0.5)*(t*t));

        }
        else
        {
            // on a smaller spread we can approximate function with 1/(1 + f(abs(angle/spread)) )
            // where f is polynomial of degree 4 with weight coef 0: 0.0
            //                                                    1: 0.0
            //                                                    2: 0.6
            //                                                    3: -0.3
            //                                                    4: 0.4
            // Note, that max argument is M_PI_2/0.0001, and in power of 4 it has a magnitude of 10^17
            // so it is only 2 digits lost from mantissa, not that bad

            // To be pedantic, we need to ensure, that 1 + polynomial is greater than 1.0
            // while argument abs(angle/spread) belongs [0, M_PI_2/0.0001] = [0, M_PI_2*10^4]
            // That is ensured

            // Details of precision err around 0 angles are not examined for now

            const double t{std::abs(angle/spread)};
            const double t2{t*t};
            const double t3{t2*t};
            const double t4{t3*t};

            return 1.0/(1.0 + 0.6*t2 - 0.3*t3 + 0.4*t4);
        }
    }


    // designed to take angle [-M_PI_2, M_PI_2] as for petal, other input results in 0.0
    double lambertian_scatterer(double angle)
    {
        if(std::abs(angle) > M_PI_2)
        {
            return 0.0;
        }
        else
        {
            return std::cos(angle);
        }
    }



    // n1, n2  > 1.0,  n1 > n2
    double critical_angle_of_TIR(double n1, double n2)
    {
        return std::asin(n2/n1);
    }

    // n1, n2  > 1.0
    // alpha [0, M_PI_2]
    // too bad contracts in C++ are not available yet
    bool is_TIR(double n1, double n2, double alpha)
    {
        if (n1 < n2)
        {
            return false;
        }

        // maybe it is better to throw exception in this case, but it is how it goes for now
        // too bad contracts in C++ are not available yet
        // if( (alpha < 0.0) || (M_PI_2 < alpha) )
        // {
        //     return false;
        // }

        if(alpha >= core::optics::critical_angle_of_TIR(n1, n2))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // n1, n2  > 1.0
    // alpha [0, M_PI_2]
    // too bad contracts in C++ are not available yet
    // before the call, check arguments via is_TIR, ensure it is not TIR
    double snell_law(double n1, double n2, double alpha)
    {
        if (n1 == n2)
        {
            // because asin(sin(alpha)) != alpha (precision errs) and it can be crucial
            return alpha;
        }
        else
        {
            return std::asin((n1/n2)*std::sin(alpha));
        }
    }

    // n1, n2  > 1.0
    // alpha, beta [0, M_PI_2]
    // return values [0.0, 1.0], in order {reflected, transmitted}
    // too bad contracts in C++ are not available yet
    // before the call, check arguments via is_TIR, ensure it is not TIR
    // we are calculating intensity coef, not amplitude
    std::pair<double, double> fresnel_intensity_coef(double n1, double n2, double alpha, double beta)
    {
        double I_r_Parallel{};
        double I_r_Perpendicular{};

        // maybe it is better to go with alpha < epsilon, for now it is like this
        if(alpha == 0.0)
        {
            I_r_Parallel = (n1-n2)/(n1+n2);
            I_r_Perpendicular = I_r_Parallel;
        }
        else
        {
            const double E_r_Parallel{ -std::tan(alpha-beta)/std::tan(alpha+beta) };
            I_r_Parallel = E_r_Parallel*E_r_Parallel;

            const double E_r_Perpendicular{ -std::sin(alpha-beta)/std::sin(alpha+beta) };
            I_r_Perpendicular = E_r_Perpendicular*E_r_Perpendicular;
        }

        // for unpolarized resulting intensity is averaged
        const double I_r{ (I_r_Parallel + I_r_Perpendicular)/2.0 };
        // conservation of energy law
        const double I_t{ 1.0 - I_r };

        return {I_r, I_t};
    }


}
