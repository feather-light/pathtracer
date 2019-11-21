/*
 * IRaytraceable interface describes an object, that can be raytraced.
 *
 */

#pragma once

#include <optional>
#include <tuple>

#include "../geometry.h"
#include "../optics.h"

namespace core::render
{
    class IRaytraceable
    {
    public:
        virtual std::optional< std::tuple<core::geometry::Point,
                                          const core::render::IRaytraceable& > > ray_intersection(const core::geometry::Ray& r) const = 0;

        virtual std::optional< std::tuple<core::geometry::Point,
                                          core::geometry::Vector,
                                          core::optics::Material,
                                          const core::render::IRaytraceable& > > probe_surface_data(const core::geometry::Ray& r) const = 0;
    };
}
