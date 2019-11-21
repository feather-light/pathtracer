#include "emitter.h"

#include "laws.h"

namespace core::optics
{
    Emitter::Emitter(const core::optics::Spectrum& spectrum, double spread) :
        spectrum_m{spectrum},
        spread_m{ (spread < 0.00001) ? 0.00001 : (1.0 < spread) ? 1.0 : spread } {}


    core::optics::Spectrum Emitter::spectrum() const
    {
        return spectrum_m;
    }

    double Emitter::spread() const
    {
        return spread_m;
    }

    // angle should be [-M_PI, M_PI],
    // as there are no other values to represent angle between vectors,
    // other than [0.0, M_PI], negative values are just for ease of use if their are ever needed,
    // since function designed to be symmetrical
    // output value [0.0, 1.0]
    double Emitter::intensity_coef(double angle) const
    {
        return core::optics::gaussian_petal(angle, spread_m);
    }
}
