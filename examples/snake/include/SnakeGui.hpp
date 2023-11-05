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

#include "SquareGui.hpp"
#include "SnakeModel.hpp"
#include "GameState.hpp"
#include "GameClock.hpp"
#include "BackgroundTexture.hpp"
#include "GameGui.hpp"

namespace blink2dgui
{
    class SnakeGui : public GameGui, public GameStateListener
    {
    public:
        SnakeGui();    // Constructor
        ~SnakeGui();   // Destructor

        void onAddEntity(const Coordinate& pos, const GridEntity& entity) override;
        void onRemoveEntity(const Coordinate& pos,  const GridEntity& entity) override;
        void onModelPropertyChange(int, int) override;
        void gameTick() override;
        void nextStep();
        void setGrid(int size) override;

    private:
        SnakeModel* snakeModel_;
        Coordinate oldHead;
        Coordinate tail;

    };
}

