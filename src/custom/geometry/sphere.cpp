#include "sphere.h"

#include <cmath>
#include <algorithm>

namespace custom::geometry
{
    Sphere::Sphere(const core::geometry::Point& center, double radius) :
        center_m{center},
        radius_m{ (radius < 0.0) ? 0.0 : radius} {}


    std::optional< std::tuple<core::geometry::Point,
                              core::geometry::Vector> > Sphere::ray_intersection(const core::geometry::Ray& ray) const
    {
        // intense work with Vectors,
        // readability is preferred over full explicit types mentioning
        using namespace core::geometry;

        // direction should be represented correctly
        auto r_d{ray.direction()};
        if(r_d.length() == 0.0)
        {
            return std::nullopt;
        }

        // Line-sphere intersection
        // in vector notation:
        //
        // Equation for sphere:
        // ||x-c||^2 = r^2
        // c is center point
        // x are points on the sphere
        // r is radius
        //
        // Equation for line (not a ray):
        // x = o + d*l
        // x are points on the line
        // o is starting point
        // d is distance along the line from the starting point
        // l is line direction (unit vector (length = 1))
        //
        // Combined, they give quadratic eq
        // Simplified, taking in account ||l||^2 = 1
        //
        // d = -(l*(o-c)) +- sqrt( (l*(o-c))^2 - ( ||o-c||^2 - r^2 ) )
        // so, result points x = o + d*l

        const Vector c{center_m};
        const double r{radius_m};

        const Vector o{ray.origin()};
        r_d.normalize();
        const Vector l{r_d};

        const Vector o_c{ subtract(o, c) };
        const double o_c_len{ o_c.length() };

        const double l_o_c{ scalar_product(l, o_c) };

        const double sqrt_arg{ l_o_c*l_o_c - o_c_len*o_c_len + r*r };

        if(sqrt_arg < 0.0)
        {
            // no line intersection
            return std::nullopt;
        }

        const double sqrt_res{std::sqrt(sqrt_arg)};
        const double d1 { -l_o_c + sqrt_res };
        const double d2 { -l_o_c - sqrt_res };

        // now, when it comes to the result
        // as we need ray intersection, not a line
        // first of all, only non-negative distance from origin is legit
        // (this reflects nature of ray as oppose to line)
        // secondly, we need to choose shorter distance,
        // since it is closer to the origin
        // (reflects the fact, that ray can have only one or none intersection point,
        // cause distance from origin can be defined)

        double d;
        const auto [min, max] = std::minmax(d1, d2);
        if(min >= 0.0)
        {
            d = min;
        }
        else
        {
            if(max >= 0.0)
            {
                d = max;
            }
            else
            {
                // if both are negative, then there is no ray intersection
                return std::nullopt;
            }
        }

        Vector shift_from_o{ l };
        shift_from_o.scale(d);
        const Point res_p { add(o, shift_from_o) };

        // normal to surface of sphere in res_p
        const Vector res_n {center_m, res_p};

        return { {res_p, res_n} };
    }
}
