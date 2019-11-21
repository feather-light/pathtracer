/*
 * IImageTile is an interface, designed to represent spectral image
 * in form of a tile.
 *
 */

#pragma once

#include <optional>
#include <utility>
#include <tuple>

#include "../optics.h"

namespace core::render
{
    class IImageTile
    {
    public:
        virtual std::optional<std::pair <int, int>> next_pixel() const = 0;
        virtual void reset() = 0;
        virtual std::optional<core::optics::Spectrum> pixel(int x, int y) const = 0;
        virtual void pixel(int x, int y, const core::optics::Spectrum& spectrum) = 0;
        virtual std::tuple<int, int, int, int> bounds() const = 0;
        virtual std::size_t spectrum_table_size() const = 0;
    };
}
