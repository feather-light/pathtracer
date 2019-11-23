# pathtracer
Physically-based spectral CPU-only renderer written in C++17 using bare STL.

![cornell_box](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/cornell_box.png)

Rendered [cornell box](https://en.wikipedia.org/wiki/Cornell_box)-like scene. Used settings: 1000 samples per pixel, recursion depth is 5, spectrum is approximated by 32 points. Note soft shadows and different reflective properties of objects. 

# About
  With growth of computational power modern rendering systems development tend to focus on implementation of physically-based approaches. That is because such techniques allow artists to shift their effort from by-hand shader modifications to the overall scene composition adjustment and increasing level of details. Instead of tweaking model's textures and baking fake light across the scene, it is now preferable to pick up a light source and material's properties from the collections of real world data.

  Although there are a lot of [PB materials and PB renderers](https://en.wikipedia.org/wiki/Physically_based_rendering), most of them are ignoring the wave nature of light, considering only geometrical optics. This simplification reduces the computational costs, but such phenomena as interference, polarization, diffraction and dispersion are ignored, so resulting images are lacking fine details. Only a few renderers are designed to work with spectral representation of light, those are called [spectral renderers](https://en.wikipedia.org/wiki/Spectral_rendering).

  **This project is focused on the implementation of the renderer, capable of processing spectral representation of light, physically-based material properties and simulation of dispersion effect.**
  
# Features
- **Path tracing implementation** – ray gathering variety to be more precise - (not to confuse with much simplified ray tracing approach).

- **BRDF is built-in** - to proper simulate light reflections and scattering.

- **Importance sampling** - allows for the more efficient rendering. 

- **Real materials can be added easily** - just pick their spectral data from the labs (e. g. light sources from CIE, reflectors from NASA’s free collection).

- **Modular approach** - allows for customization and extensibility – source code is separated into two parts: core (framework with basic utilities and declared interfaces) and custom (modules, which provide different implementations for the interfaces).

- **Documentation is available** – UML class/package diagrams are provided, check them out to learn more about architecture of the program and extensibility options.

- **Written in C++17 using only STL** – designed to rely on CPU only, it is free from unnecessary dependencies.

# Modular design usage example: path tracers
Different implementations of path tracer can be swapped without changing any other module in the system.

![pathtracers](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/pathtracers.png)

**Preview** one is used to check appearance of objects in terms of colour and perspective only.

**Depth** one might be useful to check composition details of the scene in terms of volume (which preview one is lacking).

**Reflection** one is designed to be a proper physically-based path tracer, it requires much more processing power, but produces a decent final image. 

# Modular design usage example: samplers
Different implementations of sampler can be swapped without changing any other module in the system.
Sampler is responsible for the generating a direction of the next traced ray. Below is comparison of two realizations of samplers.

**Pure random one** – generates random direction uniformly in hemisphere defined by normal to the surface. It is the most naive way to go.  

**Importance sampler** is based around BRDF importance diagram. It allows to render more efficiently by choosing sample that impacts more with a greater probability. For example, if we would make samples for the ideal mirror surface, there is really only one direction to sample. Another one is lambertian scatter - there is no reason to sample near pi/2 at all.

![samplers](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/samplers.png)

Above is comparison of two samplers applied to the same scene using same path tracer and other modules. Different amount of samples per pixel presented to demonstrate how quality changes to show efficiency of each sampler. Note that importance sampler allows for the reflections even with the smallest amount of samples, whereas pure random one is struggling with soft shadows and only tiny amount of reflection is visible when number of samples is 64, which cause metallic sphere to be almost invisible. 
It is obvious, that importance sampling strategy allows for the huge quality improvement using same computational resources.

# Tools used in development of this project
- **Arch Linux** – program was written, compiled and tested under Arch OS.

- **juCi++** – excellent lightweight C++ IDE with support for C++17 features, uses Clang and Cmake. 

- **UMLet** – very nice and simple tool to create UML diagrams via markup.

- **DevDocs** – documentation aggregator, allowing for the easy API search, has both web and standalone version.

- **PNGwriter** – easy-to-use C++ library to work with .png files.
 
# Some ideas about possible further improvements

- Implementation of parallel processing support via OpenMP.

- ISaver implementation with support of intensity correction.

- IRaytraceable scene compositor which uses space partitioning algorithm to speedup ray intersection computations.

- Serialization/deserialization of objects.

- Support for the meshes and loading of external .obj files.

- Addition of textures support.

- Modifications to implement bidirectional path tracing.

# Project author: Bondarenko Konstantin, V. N. Karazin Kharkiv National University, Kharkiv, Ukraine, 2019.
