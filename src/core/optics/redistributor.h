/*
 * Redistributor represents redirecting optical properties.
 * Such body always has a reflective properties, it may be transparent too.
 * Being a physically based model, it has an absorption spectrum
 * and a dispersion function.
 *
 */


#pragma once

#include <optional>

#include "spectrum.h"
#include "reflector.h"
#include "transmitter.h"

namespace core::optics
{
    class Redistributor
    {
    public:
        Redistributor(const core::optics::Spectrum& absorption_spectrum,
                      const core::optics::Spectrum& dispersion_function,
                      const core::optics::Reflector& reflector,
                      const std::optional<core::optics::Transmitter>& transmitter);

        core::optics::Spectrum absorption_spectrum() const;
        core::optics::Spectrum dispersion_function() const;

        core::optics::Reflector reflector() const;
        std::optional<core::optics::Transmitter> transmitter() const;

    private:
        core::optics::Spectrum absorption_spectrum_m;
        core::optics::Spectrum dispersion_function_m;

        core::optics::Reflector reflector_m;
        std::optional<core::optics::Transmitter> transmitter_m;
    };
}
