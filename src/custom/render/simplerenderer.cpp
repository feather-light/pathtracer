#include "simplerenderer.h"

namespace custom::render
{
    void SimpleRenderer::process(const core::render::IPathtracer& pathtracer,
                                 const core::render::IRaytraceable& scene,
                                 const core::render::IViewport& viewport,
                                 const core::render::ISampler& sampler,
                                 int samples,
                                 int depth,
                                 core::render::IImageTile& image) const
    {
        //getting idea about spectrum resolution to pass to the pathtracer
        const auto spectrum_table_size {image.spectrum_table_size()};
        auto pixel {image.next_pixel()};

        // iterating through all pixels image willing to give us
        while(pixel)
        {
            // casting a ray for chosen pixel,
            // call of the pathtracer
            // pixel gets obtained spectrum
            const auto [x, y] {pixel.value()};
            const auto initial_ray {viewport.cast_ray(x, y)};
            if(initial_ray)
            {
                auto spectrum { pathtracer.trace(scene,
                                                 std::nullopt,
                                                 initial_ray.value(),
                                                 sampler,
                                                 spectrum_table_size,
                                                 samples,
                                                 depth) };
                image.pixel(x, y, spectrum);
            }

            pixel = image.next_pixel();
        }
    }

}
