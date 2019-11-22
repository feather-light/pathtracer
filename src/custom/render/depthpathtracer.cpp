#include "depthpathtracer.h"

#include <cmath>

namespace custom::render
{
    core::optics::Spectrum DepthPathtracer::trace(const core::render::IRaytraceable& scene,
                                                  const std::optional<const std::reference_wrapper<const core::render::IRaytraceable> > current,
                                                  const core::geometry::Ray& initial_ray,
                                                  const core::render::ISampler& sampler,
                                                  std::size_t spectrum_table_size,
                                                  int samples,
                                                  int depth) const
    {

        // pitch black as we yet to obtain light
        core::optics::Spectrum sp { {0.0, 0.0}, spectrum_table_size};

        auto intersection { scene.ray_intersection(initial_ray) };
        if(intersection)
        {
            // using get<>() not a tie, since allows for direct initialization
            // while use of a tie requires initialization and copy-construction afterwards
            // get<>() is used with <type>, so it is secured from error of get<index>
            auto point { std::get<core::geometry::Point>(intersection.value()) };
            auto r_origin {initial_ray.origin()};
            double distance {core::geometry::distance(r_origin, point)};
            double distance_tone {1.0/(1.0 + std::log(1.0 + distance) )};
            sp = { {distance_tone, distance_tone}, spectrum_table_size };
        }

        return sp;
    }
}
