/*
 * SingleSimpleTile is a singletile implementation of an IImageTile.
 * On each pixel set call it replaces value of that pixel with a new one.
 *
 * Mutable modifiers used on counters, thoose are used in const conext,
 * but they have nothing to do with modifying the actual data state of the object,
 * just taking care of which part of the data gonna be returned next.
 *
 */

#pragma once

#include "../../core.h"

#include <vector>

namespace custom::render
{
    class SingleSimpleTile : public core::render::IImageTile
    {
    public:
        SingleSimpleTile(int width, int height, std::size_t spectrum_res);

        virtual std::optional<std::pair <int, int>> next_pixel() const override;
        virtual void reset() override;
        virtual std::optional<core::optics::Spectrum> pixel(int x, int y) const override;
        virtual void pixel(int x, int y, const core::optics::Spectrum& spectrum) override;
        virtual std::tuple<int, int, int, int> bounds() const override;
        virtual std::size_t spectrum_table_size() const override;

    private:
        std::vector< std::vector<core::optics::Spectrum> > image_m;
        mutable int current_x_m;
        mutable int current_y_m;
    };
}
