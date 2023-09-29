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

namespace blink2dgui
{
    class ShapeSelector
    {
    public:
        ShapeSelector();    // Constructor
        ~ShapeSelector();   // Destructor

        // Render the shape selector window
        void renderWindow();

        // Check if square or hexagon is selected
        bool isSquareSelected() const;
        bool isHexagonSelected() const;

    private:
        int currentShape_;  // 0 for square, 1 for hexagon
    };
}

