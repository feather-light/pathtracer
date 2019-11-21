#include "simplescene.h"

#include <algorithm>

namespace custom::render
{
    std::optional< std::tuple<core::geometry::Point,
                              const core::render::IRaytraceable& > > SimpleScene::ray_intersection(const core::geometry::Ray& r) const
    {
        // getting an intersection point from each object in the scene
        std::vector<std::tuple<core::geometry::Point,
                               const core::render::IRaytraceable& > > ps;

        for(const auto& obj : scene_m)
        {
            auto p{ obj.get().ray_intersection(r) };
            if(p)
            {
                ps.push_back(p.value());
            }
        }

        // no intersections
        if(ps.empty())
        {
            return std::nullopt;
        }


        // the closest one to the origin of the ray is a resulting one
        const auto r_origin{r.origin()};

        auto res_p{ *std::min_element(ps.begin(), ps.end(), [&r_origin](const auto& p1, const auto& p2)
                                     {
                                         using namespace core::geometry;
                                         // since we do not need actual distance,
                                         // but rather use it just as a metric,
                                         // there is no need to calculate pricey sqrt

                                         const auto& pp1 {std::get<Point>(p1)};
                                         const auto& pp2 {std::get<Point>(p2)};

                                         return distance_squared(pp1, r_origin) < distance_squared(pp2, r_origin);
                                     } ) };
        return res_p;
    }


    std::optional< std::tuple<core::geometry::Point,
                              core::geometry::Vector,
                              core::optics::Material,
                              const core::render::IRaytraceable& > > SimpleScene::probe_surface_data(const core::geometry::Ray& r) const
    {
        // find an object on a scene to probe
        const auto p{ray_intersection(r)};
        if(p)
        {
            // now only one object is tested to surface data
            // more efficient this way, cause this operation is, potentially, computationally pricey
            const auto& obj { std::get<const core::render::IRaytraceable&>(p.value()) };
            return obj.probe_surface_data(r);
        }
        else
        {
            return std::nullopt;
        }

    }


    void SimpleScene::add_object(core::render::IRaytraceable& object)
    {
        scene_m.push_back(object);
    }
}
