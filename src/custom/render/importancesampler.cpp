#include "importancesampler.h"

#include "../geometry.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

namespace custom::render
{
    ImportanceSampler::ImportanceSampler(unsigned int seed) :
        rnd_engine_m{ std::mt19937{seed} },
        uni_01_distribution_m{ std::uniform_real_distribution<double>{0.0, 1.0} },
        uni_11_distribution_m{ std::uniform_real_distribution<double>{-1.0, 1.0} },
        norm_distribution_m{},
        cos_distribution_m{ []() -> std::piecewise_linear_distribution<double>
                            {
                                // there is no distribution in standard library
                                // with cosine probability density function
                                // since it has no parameters, we can precalculate it
                                // using linear interpolation
                                // 1024 intervals should be enough
                                std::size_t samplesN {1024};
                                double left_bound {-M_PI_2};
                                double right_bound {M_PI_2};
                                double angle_step { (right_bound-left_bound)/double(samplesN)};

                                // finding out angles to find values for
                                std::vector<double> angle_samples(samplesN, angle_step);
                                angle_samples[0] = left_bound;
                                std::partial_sum(angle_samples.begin(), angle_samples.end(), angle_samples.begin());

                                //addition error might accumulate (and wavelength step precision in the first place),
                                //so we need to make sure, that right bound is correct
                                angle_samples[angle_samples.size()-1] = right_bound;

                                // calculating points
                                std::vector<double> cos_vals;
                                for(const double angle : angle_samples)
                                {
                                    cos_vals.push_back(std::cos(angle));
                                }

                                std::piecewise_linear_distribution<double> cos_pld {angle_samples.begin(), angle_samples.end(), cos_vals.begin()};

                                return cos_pld;
                            }()
                          } {}


    core::geometry::Vector ImportanceSampler::generate_sample(const core::optics::Reflector& reflector,
                                                              const core::geometry::Vector& normal_towards_incidence,
                                                              const core::geometry::Vector& specular_direction) const
    {
        double specular_probability {reflector.specular_coef()};
        double specular_or_diffuse {uni_01_distribution_m(rnd_engine_m)};

        // choosing a petal to work with a probability proportional to its the intensity part
        if(specular_or_diffuse < specular_probability)
        {
            // in specular petal now
            // inverted specular direction will help us later with creating a sample
            core::geometry::Vector specular_direction_inv {specular_direction};
            specular_direction_inv.scale(-1.0);

            // probability function for the gaussian petal is normal distribution
            double specular_roughness {reflector.specular_roughness()};

            // because, as described in laws.h for gaussian petal,
            // [0.00001, 1.0] range is normalized to 1.0 for the ease of use
            // gaussian function needs spread of [0.0001, 10] to work as intended
            specular_roughness*=10.0;
            norm_distribution_m = std::normal_distribution<double>(0.0, specular_roughness);

            // because deviation can be as much as 10, and we are using interval [0.0, M_PI/2)
            double angle { std::abs( norm_distribution_m(rnd_engine_m) ) };
            while(angle > M_PI_2)
            {
                angle = std::abs( norm_distribution_m(rnd_engine_m) );
            }

            // we need to pick a plane to which sample belongs
            // for that we need two vectors
            // first is specular direction
            // second one is random, cause shape of distribution is a figure of rotation of a petal around specular direction axis
            // by choosing directions as we do we can recreate sample ray using transmitted reconstruction function
            // but we should be aware, that it belongs to the hemisphere in relation to normal to the surface, so while loop is used
            auto cutting_plane_v { uniform_in_hemisphere_sample(specular_direction) };
            auto sample { custom::geometry::transmitted_reconstruction(cutting_plane_v, specular_direction_inv, angle) };
            while( core::geometry::angle_between(normal_towards_incidence, sample) > M_PI_2 )
            {
                angle = std::abs( norm_distribution_m(rnd_engine_m) );
                while(angle > M_PI_2)
                {
                    angle = std::abs( norm_distribution_m(rnd_engine_m) );
                }
                cutting_plane_v = uniform_in_hemisphere_sample(specular_direction);
                sample = custom::geometry::transmitted_reconstruction(cutting_plane_v, specular_direction_inv, angle);
            }

            return sample;
        }
        else
        {
            // if it is a cosine lambertian petal
            // all ideas are the same as above
            core::geometry::Vector normal_towards_incidence_inv {normal_towards_incidence};
            normal_towards_incidence_inv.scale(-1.0);

            double angle { std::abs( cos_distribution_m(rnd_engine_m) ) };
            // optional, since it should not be possible, but it does not hurt to double check
            while(angle > M_PI_2)
            {
                angle = std::abs( cos_distribution_m(rnd_engine_m) );
            }

            auto cutting_plane_v { uniform_in_hemisphere_sample(normal_towards_incidence) };
            auto sample { custom::geometry::transmitted_reconstruction(cutting_plane_v, normal_towards_incidence_inv, angle) };
            while( core::geometry::angle_between(normal_towards_incidence, sample) > M_PI_2 )
            {
                angle = std::abs( cos_distribution_m(rnd_engine_m) ) ;
                // optional, since it should not be possible, but it does not hurt to double check
                while(angle > M_PI_2)
                {
                    angle = std::abs( cos_distribution_m(rnd_engine_m) );
                }

                cutting_plane_v = uniform_in_hemisphere_sample(normal_towards_incidence);
                sample = custom::geometry::transmitted_reconstruction(cutting_plane_v, normal_towards_incidence_inv, angle) ;
            }

            return sample;
        }
    }

    core::geometry::Vector ImportanceSampler::generate_sample(const core::optics::Transmitter& transmitter,
                                                              const core::geometry::Vector& normal_towards_incidence,
                                                              const core::geometry::Vector& specular_direction) const
    {
        double specular_probability {transmitter.specular_coef()};
        double specular_or_diffuse {uni_01_distribution_m(rnd_engine_m)};

        if(specular_or_diffuse < specular_probability)
        {
            core::geometry::Vector specular_direction_inv {specular_direction};
            specular_direction_inv.scale(-1.0);
            double specular_roughness {transmitter.specular_roughness()};
            norm_distribution_m = std::normal_distribution<double>(0.0, specular_roughness);


            double angle { std::abs( norm_distribution_m(rnd_engine_m) ) };
            while(angle > M_PI_2)
            {
                angle = std::abs( norm_distribution_m(rnd_engine_m) );
            }

            auto cutting_plane_v { uniform_in_hemisphere_sample(specular_direction) };
            auto sample { custom::geometry::transmitted_reconstruction(cutting_plane_v, specular_direction_inv, angle) };
            while( core::geometry::angle_between(normal_towards_incidence, sample) > M_PI_2 )
            {
                angle = std::abs( norm_distribution_m(rnd_engine_m) );
                while(angle > M_PI_2)
                {
                    angle = std::abs( norm_distribution_m(rnd_engine_m) );
                }
                cutting_plane_v = uniform_in_hemisphere_sample(specular_direction);
                sample = custom::geometry::transmitted_reconstruction(cutting_plane_v, specular_direction_inv, angle);
            }

            return sample;
        }
        else
        {
            core::geometry::Vector normal_towards_incidence_inv {normal_towards_incidence};
            normal_towards_incidence_inv.scale(-1.0);

            double angle { std::abs( cos_distribution_m(rnd_engine_m) ) };
            // optional
            while(angle > M_PI_2)
            {
                angle = std::abs( cos_distribution_m(rnd_engine_m) );
            }

            auto cutting_plane_v { uniform_in_hemisphere_sample(normal_towards_incidence) };
            auto sample { custom::geometry::transmitted_reconstruction(cutting_plane_v, normal_towards_incidence_inv, angle) };
            while( core::geometry::angle_between(normal_towards_incidence, sample) > M_PI_2 )
            {
                angle = std::abs( cos_distribution_m(rnd_engine_m) ) ;
                // optional
                while(angle > M_PI_2)
                {
                    angle = std::abs( cos_distribution_m(rnd_engine_m) );
                }

                cutting_plane_v = uniform_in_hemisphere_sample(normal_towards_incidence);
                sample = custom::geometry::transmitted_reconstruction(cutting_plane_v, normal_towards_incidence_inv, angle) ;
            }

            return sample;
        }
    }


    // normal_towards_incidence.length() != 0.0
    core::geometry::Vector ImportanceSampler::uniform_in_hemisphere_sample(const core::geometry::Vector& normal_towards_incidence) const
    {
        core::geometry::Vector v{uni_11_distribution_m(rnd_engine_m),
                                 uni_11_distribution_m(rnd_engine_m),
                                 uni_11_distribution_m(rnd_engine_m)};
        v.normalize();
        while( (v.length() == 0.0) || (core::geometry::angle_between(normal_towards_incidence, v) > M_PI_2) )
        {
            v = core::geometry::Vector {uni_11_distribution_m(rnd_engine_m),
                                        uni_11_distribution_m(rnd_engine_m),
                                        uni_11_distribution_m(rnd_engine_m)};
            v.normalize();
        }

        return v;
    }
}
