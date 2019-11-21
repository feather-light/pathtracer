/*
 * IViewport is a an interface, which provides a view of the scene in 3D space,
 * which has corresponding rays of view for each pixel of an image.
 */

#pragma once

#include <optional>
#include "../geometry.h"

namespace core::render
{
    class IViewport
    {
    public:
        virtual std::optional<core::geometry::Ray> cast_ray(int x, int y) const = 0;
    };
}
