#include "ball.h"

namespace custom::render
{
    Ball::Ball(const custom::geometry::Sphere& sphere, const core::optics::Material& material) :
        sphere_m{sphere},
        material_m{material} {}


    std::optional<std::tuple<core::geometry::Point,
                             const core::render::IRaytraceable& > > Ball::ray_intersection(const core::geometry::Ray& r) const
    {
        const auto t { sphere_m.ray_intersection(r) };

        if(t)
        {
            return { {std::get<core::geometry::Point>(t.value()),
                      *this} };
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional< std::tuple<core::geometry::Point,
                              core::geometry::Vector,
                              core::optics::Material,
                              const core::render::IRaytraceable& > > Ball::probe_surface_data(const core::geometry::Ray& r) const
    {
        const auto t { sphere_m.ray_intersection(r) };

        if(t)
        {
            return { {std::get<core::geometry::Point>(t.value()),
                      std::get<core::geometry::Vector>(t.value()),
                      material_m,
                      *this } };
        }
        else
        {
            return std::nullopt;
        }
    }
}
