#pragma once

#include "spectrum_data.h"

#include "../core.h"

#include <map>
#include <string>

namespace materials
{
    const std::map<std::string, core::optics::Material> materials
    {
        {
            "e_D65_sharp",
            {
                "e_D65_sharp",
                {
                    {
                        {spectrums.at("D65"), 32},
                        0.8
                    }
                },
                std::nullopt
            }
        },

        {
            "r_white_marble",
            {
                "r_white_marble",
                std::nullopt,
                {{
                    { []() -> core::optics::Spectrum
                    {
                        auto dimmed {spectrums.at("white_marble")};
                        dimmed.normalize();
                        dimmed.scale(1.0);
                        return dimmed;
                    }()  , 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.9, 0.001},
                    std::nullopt
                }}
            }
        },

        {
            "r_olive_paint",
            {
                "r_olive_paint",
                std::nullopt,
                {{
                    {spectrums.at("olive_paint"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_purple",
            {
                "r_purple",
                std::nullopt,
                {{
                    {spectrums.at("purple"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_red",
            {
                "r_red",
                std::nullopt,
                {{
                    {spectrums.at("red"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_green",
            {
                "r_green",
                std::nullopt,
                {{
                    {spectrums.at("green"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_yellow",
            {
                "r_yellow",
                std::nullopt,
                {{
                    {spectrums.at("yellow"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_pink",
            {
                "r_pink",
                std::nullopt,
                {{
                    {spectrums.at("pink"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {0.0, 0.0},
                    std::nullopt
                }}
            }
        },

        {
            "r_metal_shiny",
            {
                "r_metal_shiny",
                std::nullopt,
                {{
                    { []() -> core::optics::Spectrum
                      {
                          auto D65_dimmed {spectrums.at("D65")};
                          D65_dimmed.normalize();
                          D65_dimmed.scale(0.5);
                          return D65_dimmed;
                      }()  , 32},
                    {
                        {1.0, 1.0}
                    },

                    {1.0, 0.005},
                    std::nullopt
                }}
            }
        },

        {
            "r_plastic_yellow",
            {
                "r_plastic_yellow",
                std::nullopt,
                {{
                    {spectrums.at("yellow"), 32},
                    {
                        {1.5, 1.2, 1.1, 1.1}
                    },

                    {0.1, 0.03},
                    std::nullopt
                }}
            }
        },


        {
            "r_purple_metal",
            {
                "r_purple_metal",
                std::nullopt,
                {{
                    {spectrums.at("purple"), 32},
                    {
                        {1.0, 1.0}
                    },

                    {1.0, 0.001},
                    std::nullopt
                }}
            }
        },

        {
            "r_plastic_blue",
            {
                "r_plastic_blue",
                std::nullopt,
                {{
                    {spectrums.at("blue"), 32},
                    {
                        {1.5, 1.2, 1.1, 1.1}
                    },

                    {0.4, 0.01},
                    std::nullopt
                }}
            }
        },




    };
}
