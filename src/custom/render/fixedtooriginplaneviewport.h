/*
 * FixedToOriginPlaneViewport is intended to be simple.
 * It is fixed to the global basis origin.
 * View is a plane with a set angle of perspective.
 *
 */

#pragma once

#include "../../core.h"

namespace custom::render
{
    class FixedToOriginPlaneViewport : public core::render::IViewport
    {
    public:
        FixedToOriginPlaneViewport(double width, double height, int width_res, int height_res, double horizontal_FOV);

        virtual std::optional<core::geometry::Ray> cast_ray(int x, int y) const override;

    private:
        double width_m;
        double height_m;
        int width_res_m;
        int height_res_m;
        double horizontal_FOV_m;
    };
}
