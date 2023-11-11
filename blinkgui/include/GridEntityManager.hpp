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
    class GridEntityManager
    {
    public:
        GridEntityManager(int height, int width);    // Constructor
        GridEntityManager(int height, int width, const ImVec2& windowSize, const ImVec2& windowPos);    // Constructor
        GridEntityManager() = default;    // Constructor
        ~GridEntityManager();   // Destructor

        GridEntityManager(const GridEntityManager&) = default;             // Copy constructor
        GridEntityManager& operator=(const GridEntityManager&) = default;  // Copy assignment operator

        void setTextureVector(const TextureVector& textureVector);

        void renderOn(const Coordinate& pos, const int& textureId);
        void setMoveTarget(const Coordinate& from, const Coordinate& to);
        void clearPos(const Coordinate& pos);

        void renderGrid();

        ImVec2 absolutePosition(const Coordinate& pos) const;
        Coordinate gridPosition(const ImVec2& pos) const;

    private:
        int height;           
        int width;  

        ImVec2 windowSize;
        ImVec2 windowPos;

        ImVec2 squareSize;
        ImVec2 padding;

        SDL_Texture* backgroundTexture;
        TextureVector textureVector;

        std::unordered_map<Coordinate, Img> imgMap;    
};
}

