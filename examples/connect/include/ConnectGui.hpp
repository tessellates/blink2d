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

#include "ConnectModel.hpp"
#include "GameState.hpp"
#include "GameClock.hpp"
#include "BackgroundTexture.hpp"
#include "GameGui.hpp"

namespace blink2dgui
{
    class ConnectGui : public GameGui, public GameStateListener
    {
    public:
        ConnectGui();    // Constructor
        ~ConnectGui();   // Destructor

        void onAddEntity(const Coordinate& pos, const GridEntity& entity) override;
        void onRemoveEntity(const Coordinate& pos,  const GridEntity& entity) override;
        void onModelPropertyChange(int, int) override;
        void gameTick() override;
        void setGrid(int size) override;
        void clicked(const Coordinate& pos) override;
        
    private:
        ConnectModel* connectModel_;
        bool allowPlay_ = true;
        int tickCount = 0;
    };
}

