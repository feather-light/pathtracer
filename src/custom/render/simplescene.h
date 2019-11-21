/*
 * SimpleScene is an aggregator of IRaytraceable, works as a compositor pattern.
 * Called simple, because there is no fancy algorithm to speed up intersection
 * test implemented here.
 *
 * Might be a good idea to refactor it to work with smart pointers instead of
 * references.
 */

#pragma once

#include "../../core.h"

#include <vector>
#include <functional>

namespace custom::render
{
    class SimpleScene : public core::render::IRaytraceable
    {
    public:
        virtual std::optional< std::tuple<core::geometry::Point,
                                          const core::render::IRaytraceable& > > ray_intersection(const core::geometry::Ray& r) const override;

        virtual std::optional< std::tuple<core::geometry::Point,
                                          core::geometry::Vector,
                                          core::optics::Material,
                                          const core::render::IRaytraceable& > > probe_surface_data(const core::geometry::Ray& r) const override;

        void add_object(core::render::IRaytraceable& object);

    private:
        std::vector< std::reference_wrapper<core::render::IRaytraceable> > scene_m;
    };
}
