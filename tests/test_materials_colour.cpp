#include "src/custom.h"
#include "src/materials.h"

#define _USE_MATH_DEFINES
#include <cmath>

int main()
{
    using namespace custom::geometry;
    using namespace custom::render;

    int res_x {1600};
    int res_y {900};

    SingleSimpleTile image {res_x, res_y, 32};
    const FixedToOriginPlaneViewport viewport {16, 9, res_x, res_y, 2.0*M_PI/3.0};
    const PureRandomSampler sampler {1969};
    const PreviewPathtracer preview_pathtracer;
    const DepthPathtracer depth_pathtracer;
    SimpleScene scene;
    const SimpleRenderer renderer;
    const ToPNGSaver saver {64};


    const Sphere s1 { {-18.0, 0.0, 16.0 },  4.0};
    Ball b1 { s1, materials::materials.at("r_olive_paint") };
    scene.add_object(b1);

    const Sphere s2 { {-6.0, 0.0, 16.0 },  4.0};
    Ball b2 { s2, materials::materials.at("r_purple") };
    scene.add_object(b2);

    const Sphere s3 { {+6.0, 0.0, 16.0 },  4.0};
    Ball b3 { s3, materials::materials.at("e_D65_sharp") };
    scene.add_object(b3);

    const Sphere s4 { {+18.0, 0.0, 16.0 },  4.0};
    Ball b4 { s4, materials::materials.at("r_red") };
    scene.add_object(b4);

    const Sphere s5 { {-18.0, 12.0, 16.0 },  4.0};
    Ball b5 { s5, materials::materials.at("r_yellow") };
    scene.add_object(b5);

    const Sphere s6 { {-6.0, 12.0, 16.0 },  4.0};
    Ball b6 { s6, materials::materials.at("r_green") };
    scene.add_object(b6);

    const Sphere s7 { {+6.0, 12.0, 16.0 },  4.0};
    Ball b7 { s7, materials::materials.at("r_pink") };
    scene.add_object(b7);

    double plain_radius {10.0e5};
    const Sphere s0 { {0.0, -plain_radius-9.0, 0.0 },  plain_radius};
    Ball b0 { s0, materials::materials.at("r_white_marble") };
    scene.add_object(b0);

    renderer.process(preview_pathtracer,
                     scene,
                     viewport,
                     sampler,
                     1,
                     1,
                     image);

    saver.save(image, "img/materials_test1_h.png");

    return 0;
}
