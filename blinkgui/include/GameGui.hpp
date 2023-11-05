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
#include "GameState.hpp"
#include "GameClock.hpp"

namespace blink2dgui
{
    class GameGui
    {
    public:
        GameGui();    // Constructor
        virtual ~GameGui() = default;   // Destructor

        void render();
        void changeGameSpeed(float gameSpeed);
        virtual void setGrid(int gridSize);
        virtual void gameTick() = 0;
        void backward();
        void forward();
        virtual void clicked(const Coordinate& clickedPos);

        bool play = false;
        GameClock gameClock;
        
    protected:
        SquareGui squareGui_;
        GameState* gameState_;

    };
}

