# pathtracer
Physically-based CPU-only spectral renderer written in C++17 using bare STL.

![cornell_box](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/cornell_box.png)

Rendered [cornell box](https://en.wikipedia.org/wiki/Cornell_box)-like scene. Used settings: 1000 samples per pixel, recursion depth is 5, spectrum is approximated by 32 points. Note soft shadows and different reflective properties of objects. 

# About
  With the growth of computational power modern rendering systems development tend to focus on the implementation of physically-based approaches. That is because such techniques allow artists to shift their effort from by-hand shader modifications to the overall scene composition adjustment and increasing level of details. Instead of tweaking model's textures and baking fake light across the scene, it is now preferable to pick up a light source and material's properties from the collections of real world data.

  Although there are a lot of [PB materials and PB renderers](https://en.wikipedia.org/wiki/Physically_based_rendering), most of them are ignoring the wave nature of light, considering only geometrical optics. This simplification reduces the computational costs, but such phenomena as interference, polarization, diffraction and dispersion are ignored, so resulting images are lacking fine details. Only a few renderers are designed to work with spectral representation of light. Those are called [spectral renderers](https://en.wikipedia.org/wiki/Spectral_rendering).

  **This project is focused on the implementation of the renderer, capable of processing spectral representation of light, physically-based material properties and simulation of the dispersion effect.**
  
# Features
- **[Path tracing](https://en.wikipedia.org/wiki/Path_tracing) implementation** – to be more precise, ray gathering variety (not to confuse with much simplified ray tracing approach).

- **Built-in [BRDF](https://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function)** - allows for proper simulation of light reflection and scattering.

- **[Importance sampling](http://www.pbr-book.org/3ed-2018/Monte_Carlo_Integration/Importance_Sampling.html) implementation** - allows for more efficient rendering. 

- **Real materials can be added easily** - just pick their spectral data from the labs (e. g. light sources from [CIE](https://en.wikipedia.org/wiki/International_Commission_on_Illumination), reflectors from [NASA’s free collection](https://speclib.jpl.nasa.gov/)).

- **Modular approach** - allows for customization and extensibility – source code is separated into two parts: core (framework with basic utilities and declared interfaces) and custom (modules, which provide different implementations for the interfaces).

- **Documentation is available** – [UML class/package diagrams are provided](https://github.com/feather-light/pathtracer/blob/master/docs/uml_diagrams/Pathtracer_UML.pdf), check them out to learn more about the architecture of the program and extensibility options.

- **Written in C++17 using bare STL** – designed to rely on CPU only, it is free from unnecessary dependencies.

# Modular design usage example: path tracers
Different implementations of path tracer can be swapped without changing any other module in the system.

![pathtracers](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/pathtracers.png)

**Preview** - is used to check appearance of objects in terms of colour and perspective only.

**Depth** - might be useful to check composition details of the scene in terms of volume (which preview one is lacking).

**Reflection** - is designed to be a proper physically-based path tracer, it requires much more processing power, but produces a decent final image. 

# Modular design usage example: samplers
Different implementations of sampler can be swapped without changing any other module in the system.
Sampler is responsible for generating the direction of the next traced ray. Below is the comparison of two realizations of samplers.

**Pure random one** – generates random direction uniformly in hemisphere defined by normal to the surface. It is the most naive implementation.  

**Importance sampler** is based around BRDF importance diagram. It allows more efficient rendering by choosing samples that impact more with a greater probability. For example, if we were making samples for the ideal mirror surface, there would be really only one direction to sample. Another one is Lambertian scatterer - there is no reason to sample around pi/2 at all.

![samplers](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/samplers.png)

Above is the comparison of two samplers applied to the same scene using the same path tracer and other modules. Tests with different numbers of samples per pixel are presented to show how quality changes and to demonstrate the efficiency of each sampler. Note that importance sampler allows for the reflections even with the smallest amount of samples, whereas pure random one is struggling with soft shadows and only tiny amount of reflection is visible when number of samples is 64, which cause metallic sphere to be almost invisible. 
It is obvious, that importance sampling strategy allows for the huge quality improvement using the same computational resources.

# Tools used in development of this project
- **[Arch Linux](https://wiki.archlinux.org/index.php/Arch_Linux)** – program was written, compiled and tested under Arch.

- **[juCi++](https://gitlab.com/cppit/jucipp)** – excellent lightweight C++ IDE with the support for C++17 features, uses Clang and Cmake. 

- **[UMLet](https://www.umlet.com/)** – very nice and simple tool to create UML diagrams via markup.

- **[DevDocs](https://devdocs.io/)** – documentation aggregator, allowing for the easy API search. It has both web and standalone version.

- **[PNGwriter](https://github.com/pngwriter/pngwriter)** – easy-to-use C++ library to work with .png files.
 
# Some ideas about possible further improvements

- Implementation of parallel processing support via OpenMP.

- IImageSaver implementation with the support of intensity correction.

- IRaytraceable scene compositor which uses space partitioning algorithm to speed-up ray intersection computations.

- Serialization/deserialization of objects.

- Support for meshes and loading of external .obj files.

- Addition of textures support.

- Modifications to implement bidirectional path tracing.

# Project author: Bondarenko Konstantin, V. N. Karazin Kharkiv National University, Kharkiv, Ukraine, 2019.
