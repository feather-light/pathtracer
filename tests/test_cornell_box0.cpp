#include "src/custom.h"
#include "src/materials.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

int main()
{
    using namespace custom::geometry;
    using namespace custom::render;

    int res_x {128};
    int res_y {128};

    double FOV {60*M_PI/180.0};

    SingleSimpleTile image {res_x, res_y, 32};
    const FixedToOriginPlaneViewport viewport {16, 16, res_x, res_y, FOV};
    const PureRandomSampler sampler {1967}; // 21, 22
    const PreviewPathtracer preview_pathtracer;
    const DepthPathtracer depth_pathtracer;
    const ReflectionPathtracer refl_pathtracer;
    SimpleScene scene;
    const SimpleRenderer renderer;
    //const ProgressRenderer renderer;
    const ToPNGSaver saver {64};



    double plain_radius {1.0e8};

    const Sphere s0 { {-plain_radius-8.0, 0.0 , 0.0},  plain_radius};
    Ball b0 { s0, materials::materials.at("r_red") };
    scene.add_object(b0);


    const Sphere s1 { {+plain_radius+8.0, 0.0 , 0.0},  plain_radius};
    Ball b1 { s1, materials::materials.at("r_green") };
    scene.add_object(b1);


    const Sphere s2 { {0.0, -plain_radius-8.0, 0.0},  plain_radius};
    Ball b2 { s2, materials::materials.at("r_pink") };
    scene.add_object(b2);

    const Sphere s3 { {0.0, +plain_radius+8.0, 0.0},  plain_radius};
    Ball b3 { s3, materials::materials.at("r_pink") };
    scene.add_object(b3);

    const Sphere s4 { {0.0, 0.0, +plain_radius+16.0},  plain_radius};
    Ball b4 { s4, materials::materials.at("r_pink") };
    scene.add_object(b4);


    double emitter_radius {128.0};
    double emitter_shift {0.1};
    const Sphere s5 { {0.0, emitter_radius-emitter_shift+8.0, 8.0 },  emitter_radius};
    Ball b5 { s5, materials::materials.at("e_D65_sharp") };
    scene.add_object(b5);


    const Sphere s6 { {+4.0, 0.0, 12.0 },  3.5};
    Ball b6 { s6, materials::materials.at("r_metal_shiny") };
    scene.add_object(b6);

    const Sphere s7 { {-4.0, -4.0, 4.0 },  3.99};
    Ball b7 { s7, materials::materials.at("r_plastic_yellow") };
    scene.add_object(b7);


    // std::cout << "Preview start" << std::endl;
    // renderer.process(preview_pathtracer,
    //                  scene,
    //                  viewport,
    //                  sampler,
    //                  1,
    //                  1,
    //                  image);

    // std::cout << "Preview save" << std::endl;
    // saver.save(image, "img/reflection_test_preview6.png");


    // std::cout << "Depth start" << std::endl;
    // image.reset();
    // renderer.process(depth_pathtracer,
    //                  scene,
    //                  viewport,
    //                  sampler,
    //                  1,
    //                  1,
    //                  image);

    // std::cout << "Depth save" << std::endl;
    // saver.save(image, "img/reflection_test_depth6.png");


    std::cout << "Refl start" << std::endl;
    image.reset();
    renderer.process(refl_pathtracer,
                     scene,
                     viewport,
                     sampler,
                     16,
                     3,
                     image);

    std::cout << "Refl save" << std::endl;
    saver.save(image, "img/reflection_test_refl6.png");

    return 0;
}
