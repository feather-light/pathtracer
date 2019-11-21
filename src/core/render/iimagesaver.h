/*
 * IImageSaver is an interface, which provides ability to save spectral images
 * in form of any kind of file.
 *
 */

#pragma once

#include <string>

#include "iimagetile.h"


namespace core::render
{
    class IImageSaver
    {
    public:
        virtual void save (const core::render::IImageTile& image, std::string filename) const = 0;
    };
}
