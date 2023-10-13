/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <vector>

#include <SquareGui.hpp>

namespace blink2dgui
{
    class GameGui
    {
    public:
        GameGui();    // Constructor
        ~GameGui();   // Destructor

        void render();

    private:
        SquareGui squareGui_;
    };
}

