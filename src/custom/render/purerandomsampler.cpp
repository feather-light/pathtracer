#include "purerandomsampler.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace custom::render
{
    PureRandomSampler::PureRandomSampler(unsigned int seed) :
        rnd_engine_m{ std::mt19937{seed} },
        rnd_distribution_m{ std::uniform_real_distribution<double>{-1.0, 1.0} } {}


    core::geometry::Vector PureRandomSampler::generate_sample(const core::optics::Reflector& reflector,
                                                              const core::geometry::Vector& normal_towards_incidence,
                                                              const core::geometry::Vector& specular_direction) const
    {
        return uniform_in_hemisphere_sample(normal_towards_incidence);
    }

    core::geometry::Vector PureRandomSampler::generate_sample(const core::optics::Transmitter& transmitter,
                                                              const core::geometry::Vector& normal_towards_incidence,
                                                              const core::geometry::Vector& specular_direction) const
    {
        return uniform_in_hemisphere_sample(normal_towards_incidence);
    }


    // normal_towards_incidence.length() != 0.0
    core::geometry::Vector PureRandomSampler::uniform_in_hemisphere_sample(const core::geometry::Vector& normal_towards_incidence) const
    {
        core::geometry::Vector v{rnd_distribution_m(rnd_engine_m),
                                 rnd_distribution_m(rnd_engine_m),
                                 rnd_distribution_m(rnd_engine_m)};
        v.normalize();
        while( (v.length() == 0.0) || (core::geometry::angle_between(normal_towards_incidence, v) > M_PI_2) )
        {
            v = core::geometry::Vector {rnd_distribution_m(rnd_engine_m),
                                        rnd_distribution_m(rnd_engine_m),
                                        rnd_distribution_m(rnd_engine_m)};
            v.normalize();
        }

        return v;
    }
}
