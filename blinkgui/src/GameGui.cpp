/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "GameGui.hpp"

namespace blink2dgui {

GameGui::GameGui() : gameClock(200)
{
}

void GameGui::setGrid(int gridSize)
{
    squareGui_ = SquareGui(gridSize);
}

void GameGui::render() {
    gameClock.update();
    this->gameTick();
    squareGui_.renderGrid();
}

void GameGui::backward()
{
    play = false;
    gameState_->backward();
}

void GameGui::forward()
{
    play = false;
    gameState_->forward();
}

void GameGui::changeGameSpeed(float gameSpeed)
{
    gameClock.setGameSpeed(gameSpeed);
}

void GameGui::clicked(const Coordinate& clickedPos)
{
    
}

}  // namespace blink2dgui
