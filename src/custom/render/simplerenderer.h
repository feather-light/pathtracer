/*
 * SimpleRenderer is a basic implementation of IRenderer, but it is likely,
 * that you do not need anything more complicated, than this.
 *
 */

#pragma once

#include "../../core.h"

namespace custom::render
{
    class SimpleRenderer : public core::render::IRenderer
    {
    public:
        virtual void process(const core::render::IPathtracer& pathtracer,
                             const core::render::IRaytraceable& scene,
                             const core::render::IViewport& viewport,
                             const core::render::ISampler& sampler,
                             int samples,
                             int depth,
                             core::render::IImageTile& image) const override;
    };
}
