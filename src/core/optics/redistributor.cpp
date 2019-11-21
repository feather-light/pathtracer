#include "redistributor.h"

#include <optional>

#include "spectrum.h"
#include "reflector.h"
#include "transmitter.h"

namespace core::optics
{
    Redistributor::Redistributor(const core::optics::Spectrum& absorption_spectrum,
                                 const core::optics::Spectrum& dispersion_function,
                                 const core::optics::Reflector& reflector,
                                 const std::optional<core::optics::Transmitter>& transmitter) :
        absorption_spectrum_m{absorption_spectrum},
        dispersion_function_m{dispersion_function},
        reflector_m{reflector},
        transmitter_m{transmitter} {}


    core::optics::Spectrum Redistributor::absorption_spectrum() const
    {
        return absorption_spectrum_m;
    }

    core::optics::Spectrum Redistributor::dispersion_function() const
    {
        return dispersion_function_m;
    }

    core::optics::Reflector Redistributor::reflector() const
    {
        return reflector_m;
    }

    std::optional<core::optics::Transmitter> Redistributor::transmitter() const
    {
        return transmitter_m;
    }
}
