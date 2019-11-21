/*
 * ISampler is an interface of obtaining a direction of sample, based on a
 * properties of reflector/transmitter.
 */
#pragma once

#include "../geometry.h"
#include "../optics.h"

namespace core::render
{
    class ISampler
    {
    public:
        virtual core::geometry::Vector generate_sample(const core::optics::Reflector& reflector,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const = 0;

        virtual core::geometry::Vector generate_sample(const core::optics::Transmitter& transmitter,
                                                       const core::geometry::Vector& normal_towards_incidence,
                                                       const core::geometry::Vector& specular_direction) const = 0;
    };
}
