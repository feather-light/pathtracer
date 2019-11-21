/*
 * Vector class to represent vector in 3D space.
 * Constructors with Tuple are intended to create Vector instance
 * from one or two Points.
 *
 * Methods and related functions form a standard set to work with vectors,
 * trivial stuff.
 */

#pragma once

#include "tuple.h"

namespace core::geometry
{
    class Vector: public core::geometry::Tuple
    {
    public:
        Vector(double x, double y, double z);
        Vector(const core::geometry::Tuple& t);
        Vector(const core::geometry::Tuple& start, const core::geometry::Tuple& end);

        double length() const;

        void scale(double k);
        void normalize();
    };


    Vector add(const Vector& v1, const Vector& v2);
    Vector subtract(const Vector& v1, const Vector& v2);
    double scalar_product(const Vector& v1, const Vector& v2);
    Vector vector_product(const Vector& v1, const Vector& v2);
    double triple_product(const Vector& v1, const Vector& v2, const Vector& v3);
    double angle_between(const Vector& v1, const Vector& v2);
}

