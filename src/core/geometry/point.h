/*
 * Point class represents a point in 3D space.
 * Constructor with Tuple is used to convert Vector instance to Point.
 *
 * distance is not a member function, because it has nothing to do with
 * internal data representation.
 *
 * distance_squared is the same thing, but square root is not applied,
 * so it is a bit faster.
 *
 */

#pragma once

#include "tuple.h"

namespace core::geometry
{
    class Point: public core::geometry::Tuple
    {
    public:
        Point(double x, double y, double z);
        Point(const core::geometry::Tuple& t);
    };


    double distance(const Point& p1, const Point& p2);
    double distance_squared(const Point& p1, const Point& p2);
}

