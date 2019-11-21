/*
 * PureRandomSampler just casts a random sample in a hemisphere,
 * this is as simple as it gets.
 *
 * Mutable modifiers is necessary to apply to random generators, cause each call
 * modifies them, therefore there is no other way to use them in const methods.
 *
 * Seed designed to be provided via constructor, so there is always an ability to
 * recreate exact behavior of the system.
 *
 */

#pragma once

#include "../../core.h"

#include <random>

namespace custom::render
{
    class PureRandomSampler : public core::render::ISampler
    {
    public:
        PureRandomSampler(unsigned int seed);

        virtual core::geometry::Vector generate_sample(const core::optics::Reflector& reflector,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const override;

        virtual core::geometry::Vector generate_sample(const core::optics::Transmitter& transmitter,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const override;

    private:
        mutable std::mt19937 rnd_engine_m;
        mutable std::uniform_real_distribution<double> rnd_distribution_m;

        core::geometry::Vector uniform_in_hemisphere_sample(const core::geometry::Vector& normal_towards_incidence) const;
    };
}
