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
#include <map>

#include "ConnectModel.hpp"
#include "GameState.hpp"
#include "GameClock.hpp"
#include "BackgroundTexture.hpp"
#include "GameGui.hpp"
#include "VisualEntity.hpp"

#include "RenderAction.hpp"
#include "GridEntityBuilder.hpp"
#include "RockSolidTextureManager.hpp"
#include "RockSolidModel.hpp"

namespace blink2dgui
{
    class RockSolidGui : public GameGui, public GameStateListener
    {
    public:
        RockSolidGui();    // Constructor
        ~RockSolidGui();   // Destructor

        void onAddEntity(const Coordinate& pos, const GridEntity& entity) override;
        void onRemoveEntity(const Coordinate& pos,  const GridEntity& entity) override;
        void onReplaceEntity(const Coordinate&, const GridEntity&,  const GridEntity&) override;
    
        void gameTick() override;
        void setGrid(int size) override;
        void clicked(const Coordinate& pos) override;
        
    private:
        RockSolidModel* solidModel_;
        std::map<int, VisualEntity> visualEntityMap;
        GridEntityBuilder builder;
        RockSolidTextureManager manager;
    };
}

