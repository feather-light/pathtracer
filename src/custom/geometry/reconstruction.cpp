#include "reconstruction.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace custom::geometry
{
    core::geometry::Vector reflected_reconstruction(core::geometry::Vector incidence_direction,
                                                    core::geometry::Vector normal_towards_incidence)
    {
        using namespace core::geometry;

        incidence_direction.normalize();
        normal_towards_incidence.normalize();

        auto incidence_direction_inv {incidence_direction};
        incidence_direction_inv.scale(-1.0);
        const double alpha { angle_between(incidence_direction_inv, normal_towards_incidence) };

        // actually, need to calculate some minimum angle here
        // that is suitable for further calculation and set <, but for now it is == 0.0
        if(alpha == 0.0)
        {
            return normal_towards_incidence;
        }

        if(alpha > M_PI_2)
        {
            return {0.0, 0.0, 0.0};
        }

        // creating a local basis to set a plane in which reflection takes place
        auto k {vector_product(normal_towards_incidence, incidence_direction)};
        k.normalize();
        auto t {vector_product(k, normal_towards_incidence)};
        t.normalize();

        // scaling orts to form a components of the reflected ray
        normal_towards_incidence.scale( std::cos(alpha) );
        t.scale( std::sin(alpha) );

        // reflected gonna be normalized, since unit vectors are, and sin^2 + cos^2 = 1
        auto reflected {add(normal_towards_incidence, t)};

        return reflected;
    }

    core::geometry::Vector transmitted_reconstruction(core::geometry::Vector incidence_direction,
                                                      core::geometry::Vector normal_towards_incidence,
                                                      double beta_angle)
    {
        using namespace core::geometry;

        incidence_direction.normalize();
        normal_towards_incidence.normalize();

        auto incidence_direction_inv {incidence_direction};
        incidence_direction_inv.scale(-1.0);
        const double alpha { angle_between(incidence_direction_inv, normal_towards_incidence) };

        // actually, need to calculate some minimum angle here
        // that is suitable for further calculation and set <, but for now it is == 0.0
        if(alpha == 0.0)
        {
            if(beta_angle == 0.0)
            {
                return incidence_direction;
            }
            else
            {
                return {0.0, 0.0, 0.0};
            }

        }

        if(alpha > M_PI_2)
        {
            return {0.0, 0.0, 0.0};
        }

        if( (beta_angle < 0.0) || (M_PI_2 < beta_angle) )
        {
            return {0.0, 0.0, 0.0};
        }

        // creating a local basis to set a plane in which reflection takes place
        auto k {vector_product(normal_towards_incidence, incidence_direction)};
        k.normalize();
        auto t {vector_product(k, normal_towards_incidence)};
        t.normalize();

        // scaling orts to form a components of the transmitted ray (notice a minus)
        normal_towards_incidence.scale( -std::cos(beta_angle) );
        t.scale( std::sin(beta_angle) );

        // reflected gonna be normalized, since unit vectors are, and sin^2 + cos^2 = 1
        auto transmitted {add(normal_towards_incidence, t)};

        return transmitted;
    }
}
