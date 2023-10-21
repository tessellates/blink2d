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
#include "Shape.hpp"
#include "GridEntity.hpp"

namespace blink2dgui
{
    class SquareGui
    {
    public:
        SquareGui(int griSize);    // Constructor
        SquareGui() = default;    // Constructor
        ~SquareGui();   // Destructor

        SquareGui(const SquareGui&) = default;             // Copy constructor
        SquareGui& operator=(const SquareGui&) = default;  // Copy assignment operator
        // Function to render the entire grid
        void renderGrid();
        void colorLocation(const Coordinate& pos, const ImVec4& color, bool addLayer = false);
        void moveAnimate(const Coordinate& previousPosition, const Coordinate& pos);
        void updateShapeMovement(const Coordinate& pos, float factor);
        void stopMovement(const Coordinate& pos);
        void clearPos(const Coordinate& pos);
        Shape& getShape(const Coordinate& pos);

        int gridHeight_;           
        int gridWidth_;  
    private:
        float nPixels_ = 720.0f;               // Size of the window in pixels
        float squareSize_;            // Size of each square

        ImGuiWindowFlags window_flags_;  // Flags to control window properties
        ImVec2 windowPos_;             // Position of the window

        std::vector<Shape> shapes_;  // List of centers of squares
    };
}

