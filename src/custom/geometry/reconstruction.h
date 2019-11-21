/*
 * Special set of functions to calculate a reflected and transmitted directions
 * of the ray.
 */


#pragma once

#include "../../core.h"

namespace custom::geometry
{
    core::geometry::Vector reflected_reconstruction(core::geometry::Vector incidence_direction,
                                                    core::geometry::Vector normal_towards_incidence);

    core::geometry::Vector transmitted_reconstruction(core::geometry::Vector incidence_direction,
                                                      core::geometry::Vector normal_towards_incidence,
                                                      double beta_angle);
}
