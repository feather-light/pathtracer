/*
 * Ray class is representing ray in 3D space.
 * Nothing fancy, just origin and a direction.
 */

#pragma once

#include "point.h"
#include "vector.h"

namespace core::geometry
{
    class Ray
    {
    public:
        Ray(const core::geometry::Point& origin, const core::geometry::Vector& direction);

        core::geometry::Point origin() const;
        core::geometry::Vector direction() const;

    private:
        core::geometry::Point origin_m;
        core::geometry::Vector direction_m;
    };
}
