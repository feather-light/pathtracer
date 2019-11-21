/*
 * Transmitter consists of two components - diffuse and specular.
 * Diffuse is lambert's scatter petal, and specular is gaussian petal.
 * Each component has a weight (percentage of total intensity per component)
 * Specular roughness defines spread of the gaussian petal.
 *
 * intensity_coef is method, that returns relative to max amount of intensity,
 * which is transmitted in the direction,
 * represented as angles (since radiation pattern is a sum of
 * a figure of rotation of the gaussian petal around specular axis
 * and a figure of rotation of the lamberian petal around normal to the surface).
 *
 */

#pragma once

namespace core::optics
{
    class Transmitter
    {
    public:
        Transmitter(double clearness, double specular_roughness);

        double specular_coef() const;
        double diffuse_coef() const;

        double specular_roughness() const;

        double intensity_coef(double normal_angle, double specular_angle) const;

    private:
        double specular_coef_m;
        double diffuse_coef_m;

        double specular_roughness_m;
    };
}
