/*
 * IPathtracer is an interface for a computing spectral response of 3D
 * scene in a given point within a set direction.
 *
 */

#pragma once

#include <optional>
#include <functional>

#include "../geometry.h"
#include "../optics.h"

#include "iraytraceable.h"
#include "isampler.h"

namespace core::render
{
    class IPathtracer
    {
    public:
        virtual core::optics::Spectrum trace(const core::render::IRaytraceable& scene,
                                             const std::optional<const std::reference_wrapper<const core::render::IRaytraceable> > current,
                                             const core::geometry::Ray& initial_ray,
                                             const core::render::ISampler& sampler,
                                             std::size_t spectrum_table_size,
                                             int samples,
                                             int depth) const = 0;
    };
}
