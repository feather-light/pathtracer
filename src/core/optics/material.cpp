#include "material.h"

namespace core::optics
{
    // Material may or may not have(be) an emitter, may or may not have(be) a redistributor
    // But, if none of two provided, defaults to have an emitter of nothing,
    // cause emitter is additive part, so it does not cause a recursion when rendered, and uses less memory than redistributor
    Material::Material(const std::string& name,
                       const std::optional<core::optics::Emitter>& emitter,
                       const std::optional<core::optics::Redistributor>& redistributor) :
        name_m{name},
        emitter_m{ ( !(emitter || redistributor) ) ? core::optics::Emitter{ {{0.0, 0.0}}, 1.0} : emitter },
        redistributor_m{redistributor} {}

    std::string Material::name() const
    {
        return name_m;
    }

    std::optional<core::optics::Emitter> Material::emitter() const
    {
        return emitter_m;
    }

    std::optional<core::optics::Redistributor> Material::redistributor() const
    {
        return redistributor_m;
    }
}
