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
    snakeModel_ = SnakeModel(23, 23);
    int size = 30;
    snakeModel_.listeners.push_back(this);
    squareGui_ = SquareGui((float)size);
    auto l = GridEntity(Coordinate(0,0));
    l.type = 1;
    snakeModel_.start();
    previousTick = SDL_GetTicks();
    //OnSnakeModelLocationUpdate( l );
    // Initialization code for GameGui (if any)
}

GameGui::~GameGui() {
    // Cleanup code for GameGui (if any)
}

void GameGui::render() {

    if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
        snakeModel_.changeDirection(Direction::UP);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
        snakeModel_.changeDirection(Direction::DOWN);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) {
        snakeModel_.changeDirection(Direction::RIGHT);
    }
    if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) {
        snakeModel_.changeDirection(Direction::LEFT);
    }
    int ms = 75;
    currentTick = SDL_GetTicks();
    elapsed = currentTick - previousTick;
    previousTick = currentTick;
    lag += elapsed;
    if (lag >= ms) {
        snakeModel_.nextStep();
        lag -= ms;
    }
    squareGui_.renderGrid();
}


void GameGui::OnSnakeModelUpdate() {}
void GameGui::OnVictory() {}
void GameGui::OnLose() {}

void GameGui::OnSnakeModelLocationUpdate(const GridEntity& entity) 
{
    ImVec4 color;
    if (entity.type == 0)
    {
        color = ImVec4(0, 0.5f, 0, 1);
    }
    else
    {
        color = ImVec4(0.5f, 0, 0, 1);
    }
    squareGui_.colorLocation(entity.position, color);
}
void GameGui::OnRemoveEntity(const Coordinate& pos) 
{
    ImVec4 color = ImVec4(0, 0, 0, 0);
    squareGui_.colorLocation(pos, color);
}

}  // namespace blink2dgui
