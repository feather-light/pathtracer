#include "src/custom.h"
#include "src/materials.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

int main()
{
    using namespace custom::geometry;
    using namespace custom::render;

    int res_x {512};
    int res_y {512};

    double FOV {60*M_PI/180.0};

    //SingleSimpleTile image {res_x, res_y, 32};
    SingleAdditiveTile image {res_x, res_y, 32};
    const FixedToOriginPlaneViewport viewport {16, 16, res_x, res_y, FOV};
    //const PureRandomSampler sampler {777};
    const ImportanceSampler sampler {444};
    //const PreviewPathtracer pathtracer;
    const DepthPathtracer pathtracer;
    //const ReflectionPathtracer pathtracer;
    SimpleScene scene;
    const SimpleRenderer renderer;
    const ToPNGSaver saver {64};



    // chosen radius is appropriate to the scale of other objects
    // been set above e8 it would not be able to store 1 units in mantissa
    // after power of 2, which results in noticeable err patterns below e8
    // and incalculable above
    const double plain_radius {1.0e6};

    // this section is about setting up cornell box -like scene
    const Sphere s0 { {-plain_radius-8.0, 0.0 , 0.0},  plain_radius};
    Ball b0 { s0, materials::materials.at("r_red") };
    scene.add_object(b0);


    const Sphere s1 { {+plain_radius+8.0, 0.0 , 0.0},  plain_radius};
    Ball b1 { s1, materials::materials.at("r_green") };
    scene.add_object(b1);


    const Sphere s2 { {0.0, -plain_radius-8.0, 0.0},  plain_radius};
    Ball b2 { s2, materials::materials.at("r_pink") };
    scene.add_object(b2);

    //const Sphere s3 { {0.0, +plain_radius+8.0, 0.0},  plain_radius};
    const Sphere s3 { {0.0, +plain_radius+16.0, 0.0},  plain_radius};
    Ball b3 { s3, materials::materials.at("r_pink") };
    scene.add_object(b3);

    const Sphere s4 { {0.0, 0.0, +plain_radius+16.0},  plain_radius};
    Ball b4 { s4, materials::materials.at("r_pink") };
    scene.add_object(b4);


    // emitter
    const double emitter_radius {128.0};
    const double emitter_shift {0.1};
    //const Sphere s5 { {0.0, emitter_radius-emitter_shift+8.0, 8.0 },  emitter_radius};
    const Sphere s5 { {0.0, emitter_radius-emitter_shift+16.0, 8.0 },  emitter_radius};
    Ball b5 { s5, materials::materials.at("e_D65_sharp") };
    scene.add_object(b5);


    const Sphere s6 { {0.0, 0.0, -plain_radius-0.1},  plain_radius};
    Ball b6 { s6, materials::materials.at("r_pink") };
    scene.add_object(b6);


    // objects on a scene inside the box
    const Sphere s7 { {+4.0, 0.0, 12.0 },  3.5};
    Ball b7 { s7, materials::materials.at("r_purple_metal") };
    scene.add_object(b7);

    const Sphere s8 { {-4.0, -4.0, 4.0 },  3.99};
    Ball b8 { s8, materials::materials.at("r_metal_shiny") };
    scene.add_object(b8);



     int iterations {1};
     while(iterations)
     {
         std::cout << "Rendering starts, iterations left: " << iterations << std::endl;
         image.reset();
         renderer.process(pathtracer,
                          scene,
                          viewport,
                          sampler,
                          1,
                          5,
                          image);
         iterations--;
     }


     std::cout << "Saving image" << std::endl;
     saver.save(image, "img/b0_depth.png");
     std::cout << "Done" << std::endl;

    return 0;
}
