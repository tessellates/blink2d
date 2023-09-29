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

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace blink2dgui
{
    /**
    * @class HexGui
    * Hexagonal gui
    */
    class HexGui
    {
        public:
            HexGui();
            ~HexGui();
            void renderGrid();

        private:
            void drawHexagon(const ImVec2& center, float radius, const ImVec4& color);

            float nPixels_;
            float hexRadius_;
            std::vector<ImVec2> hexCenters_;
            ImGuiWindowFlags window_flags_;
            std::vector<ImVec4> hexColors_;
            ImVec2 windowPos_;
    };
}