/*
 * Emitter consists of an emission spectrum and a spread of gaussian petal.
 * There are two getter functions.
 *
 * intensity_coef is method, that returns relative to max amount of intensity,
 * which is emitted in the direction to the surface normal,
 * represented as angle (since radiation pattern is figure of rotation of
 * a gaussian petal).
 */

#pragma once

#include "spectrum.h"

namespace core::optics
{
    class Emitter
    {
    public:
        Emitter(const core::optics::Spectrum& spectrum, double spread);

        core::optics::Spectrum spectrum() const;
        double spread() const;

        double intensity_coef(double angle) const;

    private:
        core::optics::Spectrum spectrum_m;
        double spread_m;
    };
}
