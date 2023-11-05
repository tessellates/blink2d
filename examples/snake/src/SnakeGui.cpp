/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "SnakeGui.hpp"
#include "SnakeModel.hpp"

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
    squareGui_ = SquareGui(gridSize);
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
        if (snakeModel_->snake.size() > 0)
            squareGui_.updateShapeMovement(snakeModel_->snake.front(), gameClock.getIntervalProgress());
            if (snakeModel_->snake.size() > 1)
                squareGui_.updateShapeMovement(snakeModel_->snake.back(), gameClock.getIntervalProgress());

        if (gameClock.getIntervalProgress() >= 1) {
            nextStep();
        }
    }
    else
    {
        if (snakeModel_->snake.size() > 0)
            squareGui_.updateShapeMovement(snakeModel_->snake.front(), 1);
            if (snakeModel_->snake.size() > 1)
                squareGui_.updateShapeMovement(snakeModel_->snake.back(), 1);
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
    ImVec4 color;
    if (entity.type == 0 || entity.type == 2)
    {
        color = ImVec4(0, 0.5f, 0, 1);
        squareGui_.colorLocation(entity.position, color);
        if (snakeModel_->snake.size() > 0 && play && entity.type == 0)
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

void SnakeGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    ImVec4 color = ImVec4(0, 0, 0, 0);
    if (entity.type == 2)
    {
        if (snakeModel_->snake.size() >= 3)
        {
            squareGui_.colorLocation(snakeModel_->snake.back(), ImVec4(0, 0.5f, 0, 1), true);
        }
        if (play && entity.type == 2)
            squareGui_.moveAnimate(pos, snakeModel_->snake.back());
    }
    squareGui_.clearPos(pos);
}

void SnakeGui::onModelPropertyChange(int, int) {}

}  // namespace blink2dgui
