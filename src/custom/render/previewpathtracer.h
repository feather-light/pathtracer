/*
 * PreviewPathtracer is designed to quickly preview a colour of objects in scene and
 * overall composition, before render it with a proper pbr pathtracer.
 */

#pragma once

#include "../../core.h"

namespace custom::render
{
    class PreviewPathtracer : public core::render::IPathtracer
    {
    public:
        virtual core::optics::Spectrum trace(const core::render::IRaytraceable& scene,
                                             const std::optional<const std::reference_wrapper<const core::render::IRaytraceable> > current,
                                             const core::geometry::Ray& initial_ray,
                                             const core::render::ISampler& sampler,
                                             std::size_t spectrum_table_size,
                                             int samples,
                                             int depth) const override;
    };
}
