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

#include <SquareGui.hpp>
#include <SnakeModel.hpp>
#include "GameState.hpp"
#include "GameClock.hpp"

namespace blink2dgui
{
    class GameGui : public GameStateListener
    {
    public:
        GameGui();    // Constructor
        ~GameGui();   // Destructor

        void render();

        void onAddEntity(const Coordinate& pos, const GridEntity& entity) override;
        void onRemoveEntity(const Coordinate& pos,  const GridEntity& entity) override;
        void onModelPropertyChange(int, int) override;

        void changeGameSpeed(float gameSpeed);
        void setGrid(int gridSize);
        void nextStep();
        void backward();
        void forward();

        bool play = false;

        GameClock gameClock;
    private:
        SquareGui squareGui_;
        SnakeModel snakeModel_;
        Coordinate oldHead;
        Coordinate tail;

    };
}

