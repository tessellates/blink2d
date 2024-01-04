/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "RockSolidGui.hpp"
#include "RockSolidModel.hpp"
#include "RockSolidTextureManager.hpp"
#include "GridEntityBuilder.hpp"
#include "ConnectTextures.hpp"

namespace blink2dgui {

RockSolidGui::RockSolidGui()
{
    setGrid(7);
    manager.loadTextures("assets/images/rocksolid", builder.entitySize.x);
    solidModel_->loadLevel(initializeRockSolidLevel());

}

RockSolidGui::~RockSolidGui() {
    delete gameState_;
}

void RockSolidGui::setGrid(int gridSize)
{

    gridSize = 7;
    builder = std::move(GridEntityBuilder(7, 7, ImVec2(720-90, 720-90), ImVec2(280+45, 40+45)));

    gem_ = std::move(GridEntityManager(gridSize, gridSize));
    gem_.getLayer().setTextureVector(createConnectTextureVector(builder.entitySize.x));
    gem_.getLayer().defaultInit();
    gameState_ = new RockSolidModel();
    solidModel_ = dynamic_cast<RockSolidModel*>(gameState_);
    solidModel_->listeners.push_back(this);
}

void RockSolidGui::gameTick() 
{
}

void RockSolidGui::clicked(const Coordinate& clickedPos)
{
    solidModel_->placeNodeAtPosition(clickedPos, DIRT);
}

void RockSolidGui::onAddEntity(const Coordinate& pos, const GridEntity& entity) 
{
    VisualEntity ve;
    builder.atLocation(pos);
    auto it = manager.textures.find(entity.type);
    if (it != manager.textures.end()) 
    {
        builder.instructionLayer(0).instructionTexture(it->second).addInstruction();
    }
    ve = builder.build();
    gem_.visualEntityMap.insert({pos.x + pos.y * 7, std::move(ve)});
}

void RockSolidGui::onReplaceEntity(const Coordinate& pos, const GridEntity& replaced, const GridEntity& added) 
{
    auto& ve = gem_.visualEntityMap[pos.x + pos.y * 7];
    ve.renderInstructions.clear();
    auto it = manager.textures.find(added.type);
    if (it != manager.textures.end()) 
    {
        ve.renderInstructions.push_back(RenderInstruction(std::make_unique<StaticTextureStrategy>(it->second), 0));
    }
}

void RockSolidGui::onRemoveEntity(const Coordinate& pos, const GridEntity& entity) 
{
    gem_.visualEntityMap.erase(pos.x  + pos.y * 7);
}

}  // namespace blink2dgui
