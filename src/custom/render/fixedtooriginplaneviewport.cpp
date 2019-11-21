#include "fixedtooriginplaneviewport.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace custom::render
{
    FixedToOriginPlaneViewport::FixedToOriginPlaneViewport(double width, double height, int width_res, int height_res, double horizontal_FOV) :
        width_m{ (width <= 0.0) ? 1.0 : width },
        height_m{ (height <= 0.0) ? 1.0 : height },
        width_res_m{ (width_res <= 0) ? 1 : width_res },
        height_res_m{ (height_res <= 0) ? 1 : height_res},
        horizontal_FOV_m{ (horizontal_FOV <= 0.0) ? M_PI/180.0 : (M_PI <= horizontal_FOV) ? (M_PI - M_PI/180.0) : horizontal_FOV} {}

    std::optional<core::geometry::Ray> FixedToOriginPlaneViewport::cast_ray(int x, int y) const
    {
        if( (x < 0) || (width_res_m <= x) )
        {
            return std::nullopt;
        }

        if( (y < 0) || (height_res_m <= y) )
        {
            return std::nullopt;
        }

        // ####
        // it would be a good idea to calculate those invariants once
        // maybe a point for refactoring in the future
        const double x_res{ width_m/width_res_m };
        const double y_res{ height_m/height_res_m };

        // setting beginning to the bottom left corner
        const double x_offset { -width_m/2.0 };
        const double y_offset { -height_m/2.0 };

        // setting perspective focus point
        const core::geometry::Point ray_origin { 0.0, 0.0, -(width_m/2.0)/std::tan(horizontal_FOV_m/2.0) };
        // ####

        // calculating in world position of the pixel
        const core::geometry::Point point_on_plane { x_offset + (x*x_res), y_offset + (y*y_res), 0.0 };

        // direction of perspective
        core::geometry::Vector res_v {ray_origin, point_on_plane};
        res_v.normalize();

        return  { {point_on_plane, res_v} };
    }
}
