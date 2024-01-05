/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <map>

#include "SnakeGui.hpp"
#include "SnakeModel.hpp"
#include "ConnectTextures.hpp"


namespace blink2dgui {

SnakeGui::SnakeGui() 
{
    setGrid(8);
}

SnakeGui::~SnakeGui() {
    delete gameState_;
}

void SnakeGui::setGrid(int gridSize)
{
    gameState_ = new SnakeModel(gridSize, gridSize);
    snakeModel_ = dynamic_cast<SnakeModel*>(gameState_);
    snakeModel_->listeners.push_back(this);
    gem_ = std::move(GridEntityManager(gridSize, gridSize));
    gem_.getLayer().setTextureVector(createConnectTextureVector(gem_.squareSize.x));
    gem_.getLayer().defaultInit();
    //GameGui::setGrid(gridSize);
}

void SnakeGui::gameTick() {
    static std::map<ImGuiKey, Direction> keyToDirection = {
        {ImGuiKey_UpArrow, Direction::UP},
        {ImGuiKey_DownArrow, Direction::DOWN},
        {ImGuiKey_RightArrow, Direction::RIGHT},
        {ImGuiKey_LeftArrow, Direction::LEFT}
    };

    for (const auto& [key, direction] : keyToDirection) {
        if (ImGui::IsKeyPressed(key, false) && snakeModel_->changeDirection(direction)) {
            play = true;
        }
    }

    if (play)
    {
        if (gameClock.getIntervalProgress() >= 1) {
            nextStep();
        }
    }
}

void SnakeGui::nextStep()
{
    if (snakeModel_->snake.size() > 0) 
        oldHead = snakeModel_->snake.front();
    snakeModel_->nextStep();
}

void SnakeGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
{
    if (snakeModel_->snake.size() == 1)
    {
        oldHead = snakeModel_->snake.front(); // this causes the head to not be animated on placement, however it will be animated after because once the head starts moving it becomes size 2 in between the add and remove of the tails steps. 
    }
    if (entity.type == 0 || entity.type == 2)
    {
        gem_.getLayer().renderOn(entity.position, 0);
        if (snakeModel_->snake.size() > 0 && play && entity.type == 0)
        {
            gem_.getLayer().setMoveTarget(oldHead, entity.position, false);
        }
    }
    else
    {
        gem_.getLayer().renderOn(entity.position, 1);
    }
}

void SnakeGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    if (entity.type == 2)
    {
        if (snakeModel_->snake.size() >= 3)
        {
            gem_.getLayer().renderOn(snakeModel_->snake.back(), 0);
        }
        if (play && entity.type == 2 && snakeModel_->snake.size() > 1) 
            gem_.getLayer().setMoveTarget(pos, snakeModel_->snake.back(), true);
    }
    gem_.getLayer().clearPos(pos);
}

void SnakeGui::onModelPropertyChange(int, int) {}

}  // namespace blink2dgui
