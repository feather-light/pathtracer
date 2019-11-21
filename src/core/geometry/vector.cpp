#include "vector.h"

#include <cmath>

namespace core::geometry
{
    Vector::Vector(double x, double y, double z) :
        core::geometry::Tuple(x, y, z) {}

    Vector::Vector(const core::geometry::Tuple& t) :
        core::geometry::Tuple(t) {}

    Vector::Vector(const core::geometry::Tuple& start, const core::geometry::Tuple& end) :
        core::geometry::Tuple(end.x - start.x,
                              end.y - start.y,
                              end.z - start.z) {}

    double Vector::length() const
    {
        return std::sqrt( x*x + y*y + z*z );
    }

    void Vector::scale(double k)
    {
        x*=k;
        y*=k;
        z*=k;
    }

    void Vector::normalize()
    {
        double l{ length() };
        if(l != 0.0)
        {
            scale(1.0/l);
        }
    }



    Vector add(const Vector& v1, const Vector& v2)
    {
        return Vector(v1.x + v2.x,
                      v1.y + v2.y,
                      v1.z + v2.z);
    }

    Vector subtract(const Vector& v1, const Vector& v2)
    {
        return Vector(v1.x - v2.x,
                      v1.y - v2.y,
                      v1.z - v2.z);
    }

    double scalar_product(const Vector& v1, const Vector& v2)
    {
        return ( v1.x*v2.x + v1.y*v2.y + v1.z*v2.z );
    }

    Vector vector_product(const Vector& v1, const Vector& v2)
    {
        return Vector(v1.y*v2.z - v1.z*v2.y,
                      v1.z*v2.x - v1.x*v2.z,
                      v1.x*v2.y - v1.y*v2.x);
    }

    double triple_product(const Vector& v1, const Vector& v2, const Vector& v3)
    {
        return scalar_product(v1, vector_product(v2, v3));
    }

    double angle_between(const Vector& v1, const Vector& v2)
    {
        double l1{ v1.length() };
        double l2{ v2.length() };

        //yes, test against actual equality to zero, not an epsilon precision
        if ( (l1 == 0.0) || (l2 == 0.0) )
        {
            return std::nan("");
        }

        //here the division is sequential on purpose,
        //since, having both small values (but not zero), l1*l2 can be 0
        double cos_of_angle{ scalar_product(v1, v2) / l1 };
        cos_of_angle /= l2;


        //because of floating point calculations error
        //absolute value of cos_of_angle might be more than 1
        //we need to set it back to the limit [-1, 1]
        //copysign() is chosen over trunc() to show explicit intention to get 1.0 as magnitude
        if (std::abs(cos_of_angle) > 1.0)
        {
            cos_of_angle = std::copysign(1.0, cos_of_angle);
        }

        return std::acos(cos_of_angle);
    }
}
