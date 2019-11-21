/*
 * SingleAdditiveTile is a singletile implementation of an IImageTile.
 * It is is derived from a SingleSimpleTile, because it only differs
 * in the way of treating pixel set function.
 *
 * On each pixel set call it adds value to the pixel, other than replaces it.
 * It allows for the gradual improvement of the image with each new iteration.
 *
 * Beware, that you need to call SingleSimpleTile::pixel(x, y) explicitly because
 * it is now overloaded on higher level
 * (by overridden pixel set with the different signature),
 * so it is not directly visible. Other stuff, like reset() is visible just fine.
 *
 */

#pragma once

#include "../../core.h"

#include "singlesimpletile.h"

#include <vector>

namespace custom::render
{
    class SingleAdditiveTile : public custom::render::SingleSimpleTile
    {
    public:
        SingleAdditiveTile(int width, int height, std::size_t spectrum_res);

        virtual void pixel(int x, int y, const core::optics::Spectrum& spectrum) override;
    };
}
