/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "ConnectGui.hpp"
#include "ConnectTextures.hpp"
#include "GridEntityBuilder.hpp"
#include "TextureGeneration.hpp"

void ConnectGui::init(const ImVec2& position, const ImVec2& size)
{
    visualEntityMap.clear();
    builder = std::move(GridEntityBuilder(7, 7, size, position));
    background = CreateGrid(builder.entitySize.x, size.y - builder.entitySize.x, size.x);
    squareTextures = blink2dgui::createConnectTextureVector(builder.entitySize.x);
    auto previewTextures =  blink2dgui::createConnectTextureVector(builder.entitySize.x);
    for (auto& bt : previewTextures)
    {
        SDL_SetTextureAlphaMod(bt.m_texture, 80);
        squareTextures.push_back(bt);
    }
    backgroundEntity = staticEntity(builder, {0,1}, background, 2);
}

void ConnectGui::addConnectEntity(const Coordinate& position, int color)
{
    Coordinate topDrop{0, -position.y};
    VisualEntity ve;
    if (!previewMode)
    {
       // ve = quadEntryAnimatedEntity(builder, position, 1, squareTextures[color], 1.0/5.0, 0);
        ve = entryAnimatedEntity(builder, position, topDrop, squareTextures[color], 1.0/10, 0);

    }
    else
        ve = staticEntity(builder, position, squareTextures[color+3], 0);

    //VisualEntity ve = entryAnimatedEntity(builder, position, topDrop, squareTextures[color], 1.0/7.0, 1);
    //VisualEntity ve = staticEntity(builder, position, squareTextures[color], 1);
    visualEntityMap.insert({position, std::move(ve)});
}

void ConnectGui::removeConnectEntity(const Coordinate& position)
{
    visualEntityMap.erase(position);
}

void ConnectGui::changeConnectEntity(const Coordinate& position, int color)
{
    for (auto& instruction : visualEntityMap[position].renderInstructions)
    {
        instruction.setTextureStrategy(std::make_unique<StaticTextureStrategy>(squareTextures[color + 3*previewMode]));
    }
}

bool ConnectGui::isInGui(const ImVec2& pos) const
{
    ImVec2 relative = pos - builder.gridLocation;
    if (relative.x >= 0 && relative.x < builder.gridSize.x && relative.y >= 0 && relative.y < builder.gridSize.y) {
        return true;
    }
    return false;
}

Coordinate ConnectGui::gridPosition(const ImVec2& pos) const
{
    ImVec2 relative = pos - builder.gridLocation;
    int x = (relative.x) / builder.entitySize.x;
    int y = (relative.y) / builder.entitySize.y;
    return Coordinate(x, y);
}

void ConnectGui::updateSDL()
{
    backgroundEntity.render();
    for (auto& [key, value] : visualEntityMap) {
        value.render();
    }
}