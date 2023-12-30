/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "ConnectGui.hpp"
#include "ConnectModel.hpp"
#include "ConnectTextures.hpp"
#include "GridEntityBuilder.hpp"

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
    gem_ = std::move(GridEntityManager(gridSize, gridSize));
    builder = std::move(GridEntityBuilder(7, 7, ImVec2(720-90, 720-90), ImVec2(280+45, 40+45)));
    gem_.getLayer().setTextureVector(createConnectTextureVector(builder.entitySize.x));
    std::vector<BlinkTexture> vector;
    vector.push_back(BlinkTexture(CreateTextureFromFile(Application::instance()->getRenderer(), "/Users/tobiash/Projects/DearUI/Blink2D/examples/connect/include/towerbigs.png")));
    SDL_SetTextureAlphaMod(vector[0].m_texture, 210);
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

            if (tickCount >= 1) { // Check if gameTick has been called twice after the condition is met
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
        //allowPlay_ = false;
        play = true;
        //gameClock.reset();
        connectModel_->play(clickedPos.x);
    }
}

void ConnectGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
{
    //gem_.getLayer().renderOn(entity.position, entity.type % 3);
    if (play && entity.type < 2)
    {
        
        Coordinate top = Coordinate(pos.x, 0);
        Coordinate top2 = Coordinate(0, -pos.y);
        VisualEntity ve = quadEntryAnimatedEntity(builder, pos, 7, gem_.getLayer().textureVector[entity.type % 3], 0.5, 0);
        gem_.visualEntityMap.insert(std::make_pair(pos.x  + pos.y * 7, std::move(ve)));
        //gem_.getLayer().setMoveTarget(top, entity.position);
    }
    else
    {
        VisualEntity ve = staticEntity(builder, pos, gem_.getLayer().textureVector[entity.type % 3], 0);
        gem_.visualEntityMap.insert(std::make_pair(pos.x  + pos.y * 7, std::move(ve)));
    }
}

void ConnectGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    gem_.visualEntityMap.erase(pos.x  + pos.y * 7);
    gem_.getLayer().clearPos(pos);
}

void ConnectGui::onModelPropertyChange(int, int) {}

}  // namespace blink2dgui
