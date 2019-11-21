/*
 * Basic collection of optics-related functions.
 *
 */

#pragma once

#include <utility>

namespace core::optics
{
    double gaussian_petal(double angle, double spread);
    double lambertian_scatterer(double angle);
    double critical_angle_of_TIR(double n1, double n2);
    bool is_TIR(double n1, double n2, double alpha);
    double snell_law(double n1, double n2, double alpha);
    std::pair<double, double> fresnel_intensity_coef(double n1, double n2, double alpha, double beta);
}
