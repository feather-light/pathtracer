#include "reflector.h"

#include "laws.h"

namespace core::optics
{
    Reflector::Reflector(double gloss, double specular_roughness) :
        specular_coef_m{ (gloss < 0.0) ? 0.0 : (1.0 < gloss) ? 1.0 : gloss },
        diffuse_coef_m{1.0-specular_coef_m},
        specular_roughness_m{ (specular_roughness < 0.00001) ? 0.00001 : (1.0 < specular_roughness) ? 1.0 : specular_roughness } {}


    double Reflector::specular_coef() const
    {
        return specular_coef_m;
    }

    double Reflector::diffuse_coef() const
    {
        return diffuse_coef_m;
    }


    double Reflector::specular_roughness() const
    {
        return specular_roughness_m;
    }


    // returns a coef [0.0, 1.0],
    // which represents relative amount of intensity distributed in chosen direction
    double Reflector::intensity_coef(double normal_angle, double specular_angle) const
    {
        double diffuse{ diffuse_coef_m*core::optics::lambertian_scatterer(normal_angle) };
        double specular{ specular_coef_m*core::optics::gaussian_petal(specular_angle, specular_roughness_m) };

        return diffuse + specular;
    }
}
