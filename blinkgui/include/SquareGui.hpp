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
    class SquareGui
    {
    public:
        SquareGui();    // Constructor
        ~SquareGui();   // Destructor

        // Function to draw a square given its center, size, and color
        void drawSquare(const ImVec2& center, float size, const ImVec4& color);

        // Function to render the entire grid
        void renderGrid();

    private:
        float nPixels_;               // Size of the window in pixels
        float squareSize_;            // Size of each square
        ImGuiWindowFlags window_flags_;  // Flags to control window properties
        ImVec2 windowPos_;             // Position of the window

        std::vector<ImVec2> squareCenters_;  // List of centers of squares
        std::vector<ImVec4> squareColors_;   // List of colors of squares
    };
}

