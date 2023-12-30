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
#include "GridLayer.hpp"
#include <unordered_map>
#include "VisualEntity.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <vector>

#include "VisualEntity.hpp"


namespace blink2dgui
{
    class GridEntityManager
    {
    public:
        GridEntityManager(int width, int height);    // Constructor
        GridEntityManager(int width, int height, const ImVec2& windowSize, const ImVec2& windowPos);    // Constructor
        GridEntityManager(); // = default;    // Constructor
        ~GridEntityManager();   // Destructor

        GridEntityManager(const GridEntityManager&) = delete; // Delete copy constructor
        GridEntityManager& operator=(const GridEntityManager&) = delete; // Delete copy assignment

        GridEntityManager(GridEntityManager&&) = default; // Move constructor
        GridEntityManager& operator=(GridEntityManager&&) = default; // Move assignment operator


        void renderGrid();
        void renderSDL();

        ImVec2 absolutePosition(const Coordinate& pos) const;
        ImVec2 relativePosition(const Coordinate& pos) const;
        Coordinate gridPosition(const ImVec2& pos) const;

        GridLayer& getLayer(int i = 0);

    public:
        int width;           
        int height;  

        ImVec2 windowSize;
        ImVec2 windowPos;
        ImVec2 boardSize;

        ImVec2 squareSize;
        ImVec2 padding;

        TextureVector backgroundTexture;
        TextureVector textureVector;
        
        ImGuiWindowFlags windowFlags;
        
        std::vector<GridLayer> layers;
        std::map<int, VisualEntity> visualEntityMap;
    };
}

