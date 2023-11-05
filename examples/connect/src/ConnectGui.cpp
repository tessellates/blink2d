/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "ConnectGui.hpp"
#include "ConnectModel.hpp"

namespace blink2dgui {

ConnectGui::ConnectGui()
{
    setGrid(7);
}

ConnectGui::~ConnectGui() {
    delete gameState_;
}

void ConnectGui::setGrid(int gridSize)
{
    gridSize = 7;
    squareGui_ = SquareGui(7);
    gameState_ = new ConnectModel();
    connectModel_ = dynamic_cast<ConnectModel*>(gameState_);
    connectModel_->listeners.push_back(this);
}

void ConnectGui::gameTick() {

    if (play)
    {
        squareGui_.updateShapeMovement(fallingPiece_, gameClock.getIntervalProgress());
        if (gameClock.getIntervalProgress() >= 1) 
        {
            allowPlay_ = true;
        }
    }
}

void ConnectGui::clicked(const Coordinate& clickedPos)
{
    if (allowPlay_)
    {
        play = true;
        connectModel_->play(clickedPos.x);
        allowPlay_ = false;
        gameClock.reset();
    }
}

void ConnectGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
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
    fallingPiece_ = entity.position;
    if (play)
    {
        Coordinate top = Coordinate(pos.x, 0);
        squareGui_.moveAnimate(top, entity.position);
    }
}

void ConnectGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    squareGui_.clearPos(pos);
}

void ConnectGui::onModelPropertyChange(int, int) {}

}  // namespace blink2dgui
