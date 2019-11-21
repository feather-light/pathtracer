#include "reflectionpathtracer.h"

#include "../geometry.h"

#define _USE_MATH_DEFINES
#include <cmath>


namespace custom::render
{
    core::optics::Spectrum ReflectionPathtracer::trace(const core::render::IRaytraceable& scene,
                                                       const std::optional<const std::reference_wrapper<const core::render::IRaytraceable> > current,
                                                       const core::geometry::Ray& initial_ray,
                                                       const core::render::ISampler& sampler,
                                                       std::size_t spectrum_table_size,
                                                       int samples,
                                                       int depth) const
    {
        //pinch black as we yet to obtain light
        core::optics::Spectrum sp { {0.0, 0.0}, spectrum_table_size};

        // recursion stop point + avoiding negative input
        if (depth <= 0)
        {
            return sp;
        }

        // tracing a ray
        const auto probe { scene.probe_surface_data(initial_ray) };
        if(probe)
        {
            const auto p_point { std::get<core::geometry::Point>(probe.value()) };
            const auto p_normal { std::get<core::geometry::Vector>(probe.value()) };
            const auto p_material { std::get<core::optics::Material>(probe.value()) };

            // all normals are facing away from the bodies
            // so, if we have angle less, than a pi/2,
            // ray was casted from inside of a body (which is imossible, since we never calculate transmitted light),
            // or there was a computational error
            // either way, it is not healthy at all, so we are gonna return solid nothing for an obtained light
            if(core::geometry::angle_between(p_normal, initial_ray.direction()) < M_PI_2)
            {
                return sp;
            }

            // this one is needed to calculate recursive backtrack of BRDF
            auto initial_dir_inv {initial_ray.direction()};
            initial_dir_inv.scale(-1.0);

            const auto redistributor {p_material.redistributor()};
            if(redistributor)
            {
                const auto absorption_spectrum {redistributor.value().absorption_spectrum()};
                const auto dispersion_function {redistributor.value().dispersion_function()};

                // redistributor always has a reflector
                const auto reflector {redistributor.value().reflector()};
                // initially there is no light to reflect
                core::optics::Spectrum r_sp { {0.0, 0.0}, spectrum_table_size};

                const auto wavelengths {r_sp.wavelengths()};

                // casting samples
                int samples_count{samples};
                while(samples_count > 0) // avoiding negative input also
                {
                    // this one is pointed as already reflected one
                    const auto sample_dir_inv {sampler.generate_sample(reflector, p_normal, initial_dir_inv)};

                    //this one is like it is backtracking reflection after it is done
                    auto sample_dir {sample_dir_inv};
                    sample_dir.scale(-1.0);

                    // backtracked sample is reflected
                    const auto next_probe_ray_dir {custom::geometry::reflected_reconstruction(sample_dir, p_normal)};

                    // to avoid choosing same probe point from which we are starting
                    // we need to shift origin of a ray in direction of the casted ray
                    // 10^-8 is not based around anything, just do not put anything as close together on a scene,
                    // should be specified in further revisions
                    auto shift {next_probe_ray_dir};
                    shift.normalize();
                    shift.scale(1.0e-8);
                    core::geometry::Point next_probe_ray_origin { core::geometry::add(p_point, shift) };

                    // actual next ray to trace further down recursion
                    core::geometry::Ray next_probe_ray {next_probe_ray_origin, next_probe_ray_dir};

                    // no current, cause it is reflection
                    auto sample_sp { trace(scene,
                                           std::nullopt,
                                           next_probe_ray,
                                           sampler,
                                           spectrum_table_size,
                                           samples,
                                           depth-1) };


                    // calculating a reflection coef for each wavelength, based on a dispersion function
                    // incidence angle alpha is the same for all wavelengths
                    // since the ray came from the outside of the object, it was in the vaccum/air,
                    // as objects are not allowed to cross, so n1 is 1.0
                    // no TIR checks required, cause nothing should have under 1.0 refraction coef
                    // std::vector<double> reflection_coef;
                    // const double alpha_angle {core::geometry::angle_between(p_normal, sample_dir_inv)};
                    // const double n1{1.0};
                    // for(const auto w : wavelengths)
                    // {
                    //     const double n2{dispersion_function.value_interpolated(w)};
                    //     const double beta_angle{core::optics::snell_law(n1, n2, alpha_angle)};
                    //     double i_r;
                    //     std::tie(i_r, std::ignore) = core::optics::fresnel_intensity_coef(n1, n2, alpha_angle, beta_angle);
                    //     reflection_coef.push_back(i_r);
                    // }
                    // applying to the obtained spectrum of a sample
                    //sample_sp.multiply({reflection_coef});

                    // also we need to adjust intensity of the sample according to the BRDF
                    double sample_normal_angle {core::geometry::angle_between(p_normal, sample_dir_inv)};
                    double sample_specular_angle {core::geometry::angle_between(initial_dir_inv, sample_dir_inv)};
                    double intensity_coef {reflector.intensity_coef(sample_normal_angle, sample_specular_angle)};
                    sample_sp.scale(intensity_coef);

                    // finally, sample can be added to all the others
                    r_sp.add(sample_sp);

                    samples_count--;
                }

                // obtained spectrum should be averaged over samples
                if(samples > 0) // avoiding possible negative input
                {
                    r_sp.scale(1.0/samples);
                }

                // part of the obtain light is absorbed, rather then reflected
                // it is what gives an object a specific colour
                r_sp.multiply(absorption_spectrum);

                // adding reflection part to the total result
                sp.add(r_sp);
            }

            // the last is emitter, cause it has, most probably, the biggest intensity,
            // so, if it is added first, precision may not allow for fine details from redistribution
            const auto emitter {p_material.emitter()};
            if(emitter)
            {
                auto e_sp {emitter.value().spectrum()};
                // intensity coef of emission depends on the angle of view
                const double e_intensity {emitter.value().intensity_coef( core::geometry::angle_between(p_normal, initial_dir_inv) )};
                e_sp.scale(e_intensity);

                // adding emitted light to the total result
                sp.add(e_sp);
            }

            // applying inverse squred root law
            // for a intensity fade
            // might be calculated first and be stop point of recursion, if probe is too far
            // but for now it is not so
            // const double distance_to_probe {core::geometry::distance(initial_ray.origin(), p_point)};
            // const double fading_coef {1.0/(1.0 + distance_to_probe*distance_to_probe)};
            // sp.scale(fading_coef);

            return sp;
        }
        else
        {
            // if there is no intersection with a scene, just return a black nothing
            return sp;
        }
    }
}
