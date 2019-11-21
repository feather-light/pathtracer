#include "ray.h"

namespace core::geometry
{
    Ray::Ray(const core::geometry::Point& origin, const core::geometry::Vector& direction) :
        origin_m{origin},
        direction_m{direction} {}

    core::geometry::Point Ray::origin() const
    {
        return origin_m;
    }

    core::geometry::Vector Ray::direction() const
    {
        return direction_m;
    }
}
