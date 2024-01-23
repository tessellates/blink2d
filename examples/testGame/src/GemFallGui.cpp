/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "GemFallGui.hpp"
#include "ConnectTextures.hpp"
#include "GridEntityBuilder.hpp"
#include "TextureGeneration.hpp"

void GemFallGui::init(const ImVec2& position, const ImVec2& size, int dim)
{
    visualEntityMap.clear();
    gems.clear();
    builder = std::move(GridEntityBuilder(dim, dim, size, position));
    background = CreateGrid(builder.entitySize.x, size.y, size.x);
    tmana.loadTextures("assets/images/testGame", builder.entitySize.x);
    am.framesPerTick = 8;
    backgroundEntity = staticEntity(builder, {0,0}, background, 2);
}

void GemFallGui::addSpawn(const Coordinate& position)
{
    VisualEntity ve = staticEntity(builder, position, tmana.spawner, 0);
    visualEntityMap.insert({position, std::move(ve)});
}

void GemFallGui::remove(const Coordinate& position)
{
    visualEntityMap[position].renderInstructions.clear();
    if (gems.find(position) != gems.end())
    {
        gems.erase(position);
    }
}

void GemFallGui::addGem(const Coordinate& position)
{
    if (visualEntityMap.find(position) == visualEntityMap.end())
    {
        VisualEntity ve = staticEntity(builder, position, tmana.spawner, 0);
        ve.renderInstructions.clear();
        visualEntityMap.insert({position, std::move(ve)});
    }
    gems.insert({position, &visualEntityMap[position]});

}

void GemFallGui::permGem(const Coordinate& position)
{
    visualEntityMap[position].renderInstructions.push_back({std::make_unique<StaticTextureStrategy>(tmana.pile), 4});
}

bool GemFallGui::isInGui(const ImVec2& pos) const
{
    ImVec2 relative = pos - builder.gridLocation;
    if (relative.x >= 0 && relative.x < builder.gridSize.x && relative.y >= 0 && relative.y < builder.gridSize.y) {
        return true;
    }
    return false;
}

Coordinate GemFallGui::gridPosition(const ImVec2& pos) const
{
    ImVec2 relative = pos - builder.gridLocation;
    int x = (relative.x) / builder.entitySize.x;
    int y = (relative.y) / builder.entitySize.y;
    return Coordinate(x, y);
}

void GemFallGui::updateSDL()
{
    backgroundEntity.render();
    for (auto& [key, value] : visualEntityMap) {
        value.render();
    }
}

void GemFallGui::updateVisuals(int state)
{
    am.update();
    if (am.currentFrame - frameSnap >= 8)
    {
        frameSnap = am.currentFrame;
    }

    if (am.currentFrame - frameSnap != 0 && am.currentFrame - frameSnap != 4)
    {
        return;
    }

    for(auto& [key, value] : gems)
    {
        auto ri = RenderInstruction(std::make_unique<SingleLoopTextureStrategy>(tmana.gems, &am), 3);
        value->renderInstructions.push_back(std::move(ri));
        /*
        if (value->renderInstructions.size() == 0 && am.currentFrame - frameSnap == 4)
        {

        }
        else
        {
            auto ri = RenderInstruction(std::make_unique<SingleLoopTextureStrategy>(tmana.gems, am), 3);
            value->renderInstructions.push_back(std::move(ri));
        }*/
    }

}
