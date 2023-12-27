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
#include <SDL.h>
#include <SDL_image.h>
#include "TextureVector.hpp"
#include "rendering/BlinkTexture.hpp"
#include <functional>

namespace blink2dgui
{
    class GridImg
    {
    public:
        GridImg(const ImVec2& size, const ImVec2& pos, const BlinkTexture& texture);
        GridImg() = default;    // Constructor

        GridImg(const GridImg&) = default; 
        GridImg& operator=(const GridImg&) = default;  // Copy assignment operator

        void render();
        void enableMovement(const ImVec2& sourcePosition, bool defaultAction = false);
        void setDefaultAction(const bool& defaultAction);

    private:
        ImVec2 size;           
        ImVec2 position;
        ImVec2 renderPosition;

        std::function<void()> moveAction;
        bool defaultAction = true;
        BlinkTexture texture;

        bool start = false;
    };
}

