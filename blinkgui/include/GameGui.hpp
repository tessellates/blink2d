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

        void changeGameSpeed(int gameSpeed);
        void setGrid(int gridSize);

    private:
        std::vector<Command*> commandHistory;
        CompositeStateCommand gameCycle;

        SquareGui squareGui_;
        SnakeModel snakeModel_;
        Coordinate oldHead;
        Coordinate tail;

        int gameSpeed_ = 200;
        Uint32 previousTick;
        Uint32 elapsed;
        Uint32 currentTick;
        Uint32 lag = 0;

        bool skip = false;
    };
}

