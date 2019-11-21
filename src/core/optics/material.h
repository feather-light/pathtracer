/*
 * Material consists of emitter and redistributor.
 * Although both of them are optional, if none of two provided,
 * defaults to have an emitter of nothing,
 * cause emitter is additive part,
 * so it does not cause a recursion when rendered,
 * and uses less memory than redistributor.
 *
 */

#pragma once

#include <string>
#include <optional>

#include "emitter.h"
#include "redistributor.h"

namespace core::optics
{
    class Material
    {
    public:
        Material(const std::string& name,
                 const std::optional<core::optics::Emitter>& emitter,
                 const std::optional<core::optics::Redistributor>& redistributor);

        std::string name() const;

        std::optional<core::optics::Emitter> emitter() const;
        std::optional<core::optics::Redistributor> redistributor() const;

    private:
        std::string name_m;

        std::optional<core::optics::Emitter> emitter_m;
        std::optional<core::optics::Redistributor> redistributor_m;
    };

}
