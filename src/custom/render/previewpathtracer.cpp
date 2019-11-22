#include "previewpathtracer.h"

namespace custom::render
{
    core::optics::Spectrum PreviewPathtracer::trace(const core::render::IRaytraceable& scene,
                                                    const std::optional<const std::reference_wrapper<const core::render::IRaytraceable> > current,
                                                    const core::geometry::Ray& initial_ray,
                                                    const core::render::ISampler& sampler,
                                                    std::size_t spectrum_table_size,
                                                    int samples,
                                                    int depth) const
    {

        //pitch black as we yet to obtain light
        core::optics::Spectrum sp { {0.0, 0.0}, spectrum_table_size};

        auto surface_data{ scene.probe_surface_data(initial_ray) };
        if(surface_data)
        {
            // using get<>() not a tie, since allows for direct initialization
            // while use of a tie requires initialization and copy-construction afterwards
            // get<>() is used with <type>, so it is secured from error of get<index>
            auto material { std::get<core::optics::Material>(surface_data.value()) };

            if(material.emitter())
            {
                auto e_sp{ material.emitter().value().spectrum() } ;

                // since purpose is a preview, there should be no difference in intensity
                e_sp.normalize();
                sp.add(e_sp);
            }
            else
            {
                // if there is an emitter part, it is preferred over redistribution to represent
                if(material.redistributor())
                {
                    auto a_sp{ material.redistributor().value().absorption_spectrum() };

                    // no normalizing, since should be already between [0.0, 1.0]
                    // and normalizing will cause almost black become white, for example
                    sp.add(a_sp);
                }
            }

        }

        return sp;
    }
}
