/*
 * IRenderer interface specifies class type, that is capable of obtaining a
 * spectral image of a given scene as it is seen through the defined viewport
 * via pathtracer.
 */

#pragma once

#include "ipathtracer.h"
#include "iraytraceable.h"
#include "iviewport.h"
#include "isampler.h"
#include "iimagetile.h"

namespace core::render
{
    class IRenderer
    {
    public:
        virtual ~IRenderer(){};

        virtual void process(const core::render::IPathtracer& pathtracer,
                             const core::render::IRaytraceable& scene,
                             const core::render::IViewport& viewport,
                             const core::render::ISampler& sampler,
                             int samples,
                             int depth,
                             core::render::IImageTile& image) const = 0;
    };
}
