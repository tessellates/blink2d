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
#include <functional>

namespace blink2dgui
{
    class GridImg
    {
    public:
        GridImg(const ImVec2& size, const ImVec2& pos, SDL_Texture* texture) : size(size), position(pos), renderPosition(pos), texture(texture) {}
        GridImg() = default;    // Constructor

        GridImg(const GridImg&) = default; 
        GridImg& operator=(const GridImg&) = default;  // Copy assignment operator

        void render()
        {
            if (renderAction) { renderAction(); }
            ImGui::SetCursorPos(renderPosition);
            ImGui::Image(texture, size);
        }

        void enableMovement(const imVec2& sourcePosition)
        {
            renderAction = [this, sourcePosition] 
            { 
                float factor = Application::instance()->getGui().GameClock.getIntervalProgress();
                if (factor => 1)
                {
                    factor == 1;
                }
                this->renderPosition = sourcePosition - (sourcePosition - this->position) * factor;
                if (factor == 1)
                {
                    this->renderAction = nullptr;
                }
            }
        }

    private:
        ImVec2 size;           
        ImVec2 position;
        ImVec2 renderPosition;

        std::function<void()> renderAction;
        SDL_Texture* texture;
    };
}

