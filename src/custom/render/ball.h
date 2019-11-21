/*
 * Ball is an IRaytraceable object with surface in shape of a sphere,
 * made out of certain material.
 *
 */

#pragma once

#include "../../core.h"
#include "../geometry.h"

namespace custom::render
{
    class Ball : public core::render::IRaytraceable
    {
    public:
        Ball(const custom::geometry::Sphere& sphere, const core::optics::Material& material);

        virtual std::optional< std::tuple<core::geometry::Point,
                                          const core::render::IRaytraceable& > > ray_intersection(const core::geometry::Ray& r) const override;

        virtual std::optional< std::tuple<core::geometry::Point,
                                          core::geometry::Vector,
                                          core::optics::Material,
                                          const core::render::IRaytraceable& > > probe_surface_data(const core::geometry::Ray& r) const override;

    private:
        custom::geometry::Sphere sphere_m;
        core::optics::Material material_m;
    };
}
