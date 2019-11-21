/*
 * Sphere in 3D space.
 * Can calculate ray intersection with itself.
 */

#pragma once

#include "../../core.h"

#include <optional>
#include <tuple>

namespace custom::geometry
{
    class Sphere
    {
    public:
        Sphere(const core::geometry::Point& center, double radius);

        std::optional< std::tuple<core::geometry::Point,
                                  core::geometry::Vector> > ray_intersection(const core::geometry::Ray& ray) const;

    private:
        core::geometry::Point center_m;
        double radius_m;
    };
}
