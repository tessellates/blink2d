/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "GameGui.hpp"
#include "SnakeModel.hpp"

namespace blink2dgui {

GameGui::GameGui() 
{
    setGrid(8);
}

GameGui::~GameGui() {
    // Cleanup code for GameGui (if any)
}

void GameGui::setGrid(int gridSize)
{
    squareGui_ = SquareGui(gridSize);
    snakeModel_ = SnakeModel(gridSize, gridSize);
    snakeModel_.listeners.push_back(this);
    //skip = true;
    //snakeModel_.start();
    previousTick = SDL_GetTicks();
}

void GameGui::render() {
    if (skip)
    {
        skip = false;
        return;
    }
    static std::map<ImGuiKey, Direction> keyToDirection = {
        {ImGuiKey_UpArrow, Direction::UP},
        {ImGuiKey_DownArrow, Direction::DOWN},
        {ImGuiKey_RightArrow, Direction::RIGHT},
        {ImGuiKey_LeftArrow, Direction::LEFT}
    };

    currentTick = SDL_GetTicks();
    elapsed = currentTick - previousTick;
    previousTick = currentTick;
    lag += elapsed;

    for (const auto& [key, direction] : keyToDirection) {
        if (ImGui::IsKeyPressed(key, false) && snakeModel_.changeDirection(direction)) {
            //if (lag < gameSpeed_/2)
            //    lag = gameSpeed_/2;
        }
    }

    if (snakeModel_.snake.size() > 0)
        squareGui_.updateShapeMovement(snakeModel_.snake.front(), (float)lag/(float)gameSpeed_);
        if (snakeModel_.snake.size() > 1)
            squareGui_.updateShapeMovement(snakeModel_.snake.back(), (float)lag/(float)gameSpeed_);

    if (lag >= gameSpeed_) {
        if (snakeModel_.snake.size() > 0) 
            oldHead = snakeModel_.snake.front();
        snakeModel_.nextStep(gameCycle);
        
        lag -= gameSpeed_;
    }
    squareGui_.renderGrid();
}

void GameGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
{
    ImVec4 color;
    if (entity.type == 0)
    {
        color = ImVec4(0, 0.5f, 0, 1);
        squareGui_.colorLocation(entity.position, color);
        if (snakeModel_.snake.size() > 0)
        {
            squareGui_.moveAnimate(oldHead, entity.position);
        }
    }
    else
    {
        color = ImVec4(0.5f, 0, 0, 1);
        squareGui_.colorLocation(entity.position, color);
    }
}

void GameGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    ImVec4 color = ImVec4(0, 0, 0, 0);
    if (snakeModel_.snake.size() >= 3)
    {
        squareGui_.colorLocation(snakeModel_.snake.back(), ImVec4(0, 0.5f, 0, 1), true);
    }
    squareGui_.moveAnimate(pos, snakeModel_.snake.back());

    squareGui_.clearPos(pos);
}

void GameGui::onModelPropertyChange(int, int) {}


void GameGui::changeGameSpeed(int gameSpeed)
{
    gameSpeed_ = gameSpeed;
    lag = 0;
}

}  // namespace blink2dgui
