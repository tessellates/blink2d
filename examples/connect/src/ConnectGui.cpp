/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "ConnectGui.hpp"
#include "ConnectModel.hpp"
#include "ConnectTextures.hpp"

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
    gem_ = GridEntityManager(7, 7);
    
    gem_.getLayer().setTextureVector(createConnectTextureVector(gem_.squareSize.x));
    std::vector<BlinkTexture> vector;
    vector.push_back(BlinkTexture(CreateTextureFromFile(Application::instance()->getRenderer(), "/Users/tobiash/Projects/DearUI/Blink2D/examples/connect/include/towerbigs.png")));
    SDL_SetTextureAlphaMod(vector[0].m_texture, 60);
    gem_.getLayer(1).addBackgroundTextures(vector);
    gem_.getLayer().defaultInit();
    gameState_ = new ConnectModel();
    connectModel_ = dynamic_cast<ConnectModel*>(gameState_);
    connectModel_->listeners.push_back(this);
}

void ConnectGui::gameTick() {

    if (play) {
        if (gameClock.getIntervalProgress() >= 1) {
            tickCount++;

            if (tickCount >= 2) { // Check if gameTick has been called twice after the condition is met
                allowPlay_ = true;
                tickCount = 0; // Reset the counter for the next round
                connectModel_->fireWin();
            }
        }
    }
}

void ConnectGui::clicked(const Coordinate& clickedPos)
{
    if (allowPlay_)
    {
        allowPlay_ = false;
        play = true;
        gameClock.reset();
        connectModel_->play(clickedPos.x);
    }
}

void ConnectGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
{
    gem_.getLayer().renderOn(entity.position, entity.type % 3);
    if (play && entity.type < 2)
    {
        Coordinate top = Coordinate(pos.x, 0);
        gem_.getLayer().setMoveTarget(top, entity.position);
    }
}

void ConnectGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    gem_.getLayer().clearPos(pos);
}

void ConnectGui::onModelPropertyChange(int, int) {}

}  // namespace blink2dgui
