# pathtracer
Physically-based spectral CPU-only renderer written in C++17 using bare STL.

![cornell_box](https://github.com/feather-light/pathtracer/blob/master/docs/output_examples/cornell_box.png)

Rendered cornell box-like scene. Used settings: 1000 samples per pixel, recursion depth is 5, spectrum is approximated by 32 points. Note soft shadows and different reflective properties of objects. 

# About
  With growth of computational power modern rendering systems development tend to focus on implementation of physically-based approaches. That is because such techniques allow artists to shift their effort from by-hand shader modifications to the overall scene composition adjustment and increasing level of details. Instead of tweaking model's textures and baking fake light across the scene, it is now preferable to pick up a light source and material's properties from the collections of real world data.

  Although there are a lot of PB materials and PB renderers, most of them are ignoring the wave nature of light, considering only geometrical optics. This simplification reduces the computational costs, but such phenomena as interference, polarization, diffraction and dispersion are ignored, so resulting images are lacking fine details. Only a few renderers are designed to work with spectral representation of light, those are called spectral renderers.

  **This project is focused on the implementation of the renderer, capable of processing spectral representation of light, physically-based material properties and simulation of dispersion effect.**
  
# Features
- **Path tracing implementation** – ray gathering variety to be more precise - (not to confuse with much simplified ray tracing approach).

- **BRDF is built-in** - to proper simulate light reflections and scattering.

- **Importance sampling** - allows for the more efficient rendering. 

- **Real materials can be added easily** - just pick their spectral data from the labs (e. g. light sources from CIE, reflectors from NASA’s free collection).

- **Modular approach** - allows for customization and extensibility – source code is separated into two parts: core (framework with basic utilities and declared interfaces) and custom (modules, which provide different implementations for the interfaces).

- **Documentation is available** – UML class/package diagrams are provided, check them out to learn more about architecture of the program and extensibility options.

- **Written in C++17 using only STL** – designed to rely on CPU only, it is free from unnecessary dependencies.



 

