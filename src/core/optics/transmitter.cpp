#include "transmitter.h"

#include "laws.h"

namespace core::optics
{
    Transmitter::Transmitter(double clearness, double specular_roughness) :
        specular_coef_m{ (clearness < 0.0) ? 0.0 : (1.0 < clearness) ? 1.0 : clearness },
        diffuse_coef_m{1.0-specular_coef_m},
        specular_roughness_m{ (specular_roughness < 0.00001) ? 0.00001 : (1.0 < specular_roughness) ? 1.0 : specular_roughness } {}


    double Transmitter::specular_coef() const
    {
        return specular_coef_m;
    }

    double Transmitter::diffuse_coef() const
    {
        return diffuse_coef_m;
    }


    double Transmitter::specular_roughness() const
    {
        return specular_roughness_m;
    }

    // returns a coef [0.0, 1.0],
    // which represents relative amount of intensity distributed in chosen direction
    double Transmitter::intensity_coef(double normal_angle, double specular_angle) const
    {
        double diffuse{ diffuse_coef_m*core::optics::lambertian_scatterer(normal_angle) };
        double specular{ specular_coef_m*core::optics::gaussian_petal(specular_angle, specular_roughness_m) };

        return diffuse + specular;
    }
}
