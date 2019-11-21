/*
 * Tuple is meant to be base class for Point and Vector,
 * since there should be ability to treat point as radius vector and visa-versa.
 * Whole point is that cross-dependency(awareness) of Point and Vector
 * is very ugly, and they have same exact data structure.
 *
 * Components are public for the ease of use in complex geometry formulas.
 * Since there are no methods, instances of tuple are meaningless,
 * so protected destructor and constructor is a way to go.
 *
 */

#pragma once

namespace core::geometry
{
    class Tuple
    {
    public:
        double x;
        double y;
        double z;

    protected:
        Tuple(double x, double y, double z);
        ~Tuple() = default;
    };
}
