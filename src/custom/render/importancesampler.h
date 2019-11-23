/*
 * ImportanceSampler is based around BRDF importance diagram.
 * It allows to render more efficiently by choosing sample that
 * impacts more value with a greater probability.
 * Example given - if we would make samples for the ideal mirror, there is only
 * one direction to sample, really.
 * Another one is lambertian scatter - there is no reason to sample near
 * pi/2 at all.
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
    class ImportanceSampler : public core::render::ISampler
    {
    public:
        ImportanceSampler(unsigned int seed);

        virtual core::geometry::Vector generate_sample(const core::optics::Reflector& reflector,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const override;

        virtual core::geometry::Vector generate_sample(const core::optics::Transmitter& transmitter,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const override;

    private:
        mutable std::mt19937 rnd_engine_m;
        mutable std::uniform_real_distribution<double> uni_01_distribution_m;
        mutable std::uniform_real_distribution<double> uni_11_distribution_m;
        mutable std::normal_distribution<double> norm_distribution_m;
        mutable std::piecewise_linear_distribution<double> cos_distribution_m;

        core::geometry::Vector uniform_in_hemisphere_sample(const core::geometry::Vector& normal_towards_incidence) const;
    };
}
