#include "spectrum.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

namespace core::optics
{
    Spectrum::Spectrum(const std::vector<double>& table) :
        table_m{ (table.size() < 2) ? std::vector<double>{0.0, 0.0} :  table } {}

    Spectrum::Spectrum(const Spectrum& s, std::size_t table_size) :
        Spectrum(std::vector<double>(table_size))
    {
        if(table_size >= 2)
        {
            if(table_size == s.table_size())
            {
                table_m = s.table_m;
            }
            else
            {
                // then we need to make downscale or upscale
                // either way, there are gonna be new wavelengths as table points
                // so, as they should represent average value of function around that point
                // average value can be calculated as integral(x [a,b])/(b-a)

                // since we need to get area borders around wavelength`s table points
                // we can add one more wavelength point on the right with same wavelength step and
                // then just shift all of them by a half of wavelength step to the left
                auto Nws{ wavelengths() };
                Nws.push_back(max_wavelength_s + wavelength_step());
                double half_of_wavelength_step{ wavelength_step()/2.0 };
                for(auto& w : Nws)
                {
                    w -= half_of_wavelength_step;
                }
                // now, imagine wavelengths for table as "i"
                // and wavelengths in Nws as "|"
                // and keep in mind, that there are half of wavelength step between them
                // it looks like this for table_size == 4, for example:
                // "|i|i|i|i|"


                // now Sws is necessary to get information of what exact wavelengths points are stored in s
                auto Sws{ s.wavelengths() };
                double l{0.0};
                double r{0.0};
                for(std::size_t i = 0; i < Nws.size()-1; ++i)
                {
                    //each sequential pair forms a bound of integral to average
                    l = Nws[i];
                    r = Nws[i+1];


                    // now using trapezoidal method to calculate integral,
                    // (which is convenient, appropriate and accurate, since we utilize linear interpolation),
                    // we need to get points to work with
                    // they can be find in Sws, or not(if it is upscale)
                    std::vector<double> ws{};
                    std::copy_if(Sws.begin(), Sws.end(), std::back_inserter(ws), [l,r](double w)
                    {
                        return ( (l <= w) && (w <= r) );
                    });

                    // now we need to add left and right bound
                    // no need to check if they already are there
                    // cause if they are, it would not hurt to calculate area of two more trapezoids
                    // although each of them might be 0, if the bound was already included
                    // on the other hand, applying 2 find operations to potentially big vectors is not efficient
                    ws.push_back(l);
                    ws.push_back(r);
                    // but sort is required to put things in order (which would be a thing if left bound was missing anyway)
                    std::sort(ws.begin(), ws.end());

                    // now for each pair we calculate area of trapezoid
                    // because steps between wavelegths are not equal, it is this way,
                    // no mathematical optimizations to calculate integral altogether could be utilized, but it is not too bad
                    double integral{0.0};
                    double a{0.0};
                    double b{0.0};
                    for(std::size_t j = 0; j < ws.size()-1; ++j)
                    {
                        a = ws[j];
                        b = ws[j+1];
                        integral += (b-a)*(s.value_interpolated(a) + s.value_interpolated(b))/2.0;
                    }

                    // so to the table goes averaged value, which is the whole point
                    table_m[i] = integral/(r-l);
                }
            }
        }
        // otherwise it is already defaulted to 0.0, 0.0 (pinch black) as fault init
    }

    Spectrum::Spectrum(const std::vector<double>& table, std::size_t table_size) :
        Spectrum(Spectrum(table), table_size) {}



    double Spectrum::min_wavelength() const
    {
        return min_wavelength_s;
    }

    double Spectrum::max_wavelength() const
    {
        return max_wavelength_s;
    }

    std::size_t Spectrum::table_size() const
    {
        return table_m.size();
    }

    double Spectrum::wavelength_step() const
    {
        return (max_wavelength_s - min_wavelength_s)/(table_size()-1);
    }

    double Spectrum::value_interpolated(double wavelength) const
    {
        if( !( (min_wavelength_s <= wavelength) && (wavelength <= max_wavelength_s) ) )
        {
            return 0.0;
        }

        // to keep it simple and fast it is linear between two points

        // interval`s number is table_size-1
        // interval 0 is positions [0] and [1] in data vector
        // interval 1 is [1] and [2], etc.
        int interval{ int( (wavelength - min_wavelength_s)/wavelength_step() ) };

        // in case of max wavelength we need to avoid "last pole err"
        if( interval == int(table_size()) )
        {
            --interval;
        }


        // getting coordinates for points
        double x0{min_wavelength_s + interval*wavelength_step()};
        double x1{x0 + wavelength_step()};

        double y0{table_m[interval]};
        double y1{table_m[interval+1]};

        // linear function : y = k*x + b
        double k{ (y0-y1)/(x0-x1) };
        double b{ y0-k*x0 };

        return (k*wavelength + b);
    }


    std::vector<double> Spectrum::wavelengths() const
    {
        std::vector<double> ws(table_size(), wavelength_step());
        ws[0] = min_wavelength_s;
        std::partial_sum(ws.begin(), ws.end(), ws.begin());

        // addition error might accumulate (and wavelength step precision in the first place),
        // so we need to make sure, that right bound is correct
        ws[table_size()-1] = max_wavelength_s;

        return ws;
    }

    double Spectrum::integral() const
    {
        // naturally, trapezoidal method is used
        // since grid is uniform we can use formula
        // I = h*( (f0 + fn)/2 + sum[i:1..n-1](fi) ) + err
        // but we can slightly change it to avoid messing with 1 and n-1 iterators range
        // I = h*(sum[i:0..n](fi) - (f0 + fn)/2 ) + err
        // same stuff, but more explicit to code

        // from here, there are some aspects to consider
        // Since floating point calculations are not associative (a+b)+c != a+(b+c)
        // Do we need to get same exact result on the same data set?
        // Yes: then we need to use std::accumulate, since it folds
        // No: then std::reduce can be applied, it is unordered, but faster due to that
        // If precision is important, then data can be sorted before the accumulate fold,
        // so we are saving tail of mantissa by adding small numbers first
        // (may go even further and find two smallest to add next again after each sum to ensure best possible accuracy)

        // For now, i would prefer deterministic consistency of accumulate.
        // Common size of table would not be over 64,
        // so parallelism may not even make that much of a difference.
        // No reason to slow things down in favor of precision, so no sort for now.

        return wavelength_step() * ( std::accumulate(table_m.begin(), table_m.end(), 0.0) - (table_m.front()+table_m.back())/2.0 );

    }

    void Spectrum::scale(double k)
    {
        // note: std::transform can be used instead, with a potential for unsequenced computations
        // but typical table size is too small to benefit from parallel execution
        // might be even slower
        for(auto& w : table_m)
        {
            w *= k;
        }
    }

    void Spectrum::normalize()
    {
        double max{ *std::max_element(table_m.begin(), table_m.end()) };
        if(max != 0.0)
        {
            scale(1.0/max);
        }
    }

    void Spectrum::add(const Spectrum& s)
    {
        // adjusting size of the second operand via suitable constructor
        if(table_size() != s.table_size())
        {
            add(Spectrum(s, table_size()));
        }
        else
        {
            // using transform as simple and explicit way, also parallel policy might be applied if desired
            // but it may be more harm than anything on a typically small table size
            std::transform(table_m.begin(), table_m.end(), s.table_m.begin(), table_m.begin(), std::plus<double>());
        }
    }

    void Spectrum::multiply(const Spectrum& s)
    {
        // adjusting size of the second operand via suitable constructor
        if(table_size() != s.table_size())
        {
            multiply(Spectrum(s, table_size()));
        }
        else
        {
            // using transform as simple and explicit way, also parallel policy might be applied if desired
            // but parallel policy may be more harm than anything on a typically small table size
            std::transform(table_m.begin(), table_m.end(), s.table_m.begin(), table_m.begin(), std::multiplies<double>());
        }

    }


}
