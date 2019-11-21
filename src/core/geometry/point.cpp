#include "point.h"

#include <cmath>

namespace core::geometry
{
    Point::Point(double x, double y, double z) :
        core::geometry::Tuple(x, y, z) {}

    Point::Point(const core::geometry::Tuple& t) :
        core::geometry::Tuple(t) {}

    double distance(const Point& p1, const Point& p2)
    {
        double dx = (p2.x - p1.x);
        double dy = (p2.y - p1.y);
        double dz = (p2.z - p1.z);

        return std::sqrt( dx*dx + dy*dy + dz*dz );
    }

    double distance_squared(const Point& p1, const Point& p2)
    {
        double dx = (p2.x - p1.x);
        double dy = (p2.y - p1.y);
        double dz = (p2.z - p1.z);

        return ( dx*dx + dy*dy + dz*dz );
    }
}
