#include "singleadditivetile.h"

namespace custom::render
{
    SingleAdditiveTile::SingleAdditiveTile(int width, int height, std::size_t spectrum_res) :
        custom::render::SingleSimpleTile(width, height, spectrum_res) {}



    void SingleAdditiveTile::pixel(int x, int y, const core::optics::Spectrum& spectrum)
    {
        // this is is more elegant way to implement it from the design perspective

        // might be implemented in more efficient way in terms of computational speed
        // by declaring image_m in base class as protected, so we woud be able to
        // add spectrums directly without function calls

        // need to call SingleSimpleTile::pixel(x, y) explicitly because
        // it is now overloaded on higher level
        // (by overridden pixel set with the different signature), so it is not
        // directly visible. Other stuff, like reset() is visible just fine.
        auto s_xy{ SingleSimpleTile::pixel(x, y) };
        if(s_xy)
        {
            // addition here!
            // not an assignment
            s_xy.value().add(spectrum);

            // now assignment via base class function
            SingleSimpleTile::pixel(x, y, s_xy.value());
        }

    }
}
