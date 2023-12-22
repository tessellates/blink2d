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
#include "GridImg.hpp"
#include <unordered_map>

namespace blink2dgui
{
    class GridLayer
    {
    public:
        GridLayer() = default;    // Constructor
        GridLayer(const std::function<ImVec2(Coordinate)>& conversionFunction, const ImVec2& windowSize, const ImVec2& squareSize);    // Constructor
        ~GridLayer();   // Destructor

        void setTextureVector(const std::vector<BlinkTexture>& textureVector);
        void addBackgroundTextures(const std::vector<BlinkTexture>& textureVector);

        void renderOn(const Coordinate& pos, const int& textureId);
        void setMoveTarget(const Coordinate& from, const Coordinate& to, const bool& defaultAction = false);
        void clearPos(const Coordinate& pos);

        void renderGrid();
        void defaultInit();
    public:
        std::vector<GridImg> backgroundTextures;
        std::vector<BlinkTexture> textureVector;
        std::unordered_map<Coordinate, GridImg> imgMap;
        std::function<ImVec2(const Coordinate&)> absolutePosition;
        ImVec2 windowSize;
        ImVec2 squareSize;
};

}

