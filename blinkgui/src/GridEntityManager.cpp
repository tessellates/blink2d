/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "GridEntityManager.hpp"

namespace blink2dgui
{

    GridEntityManager::GridEntityManager(int height, int width, const ImVec2& windowSize, const ImVec2& windowPos) : height(height), width(width), windowSize(windowSize), windowPos(windowPos) 
    {
        squareSize_ = (float) nPixels_ / (gridSize + 1);
        window_flags_ = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        squareSize = ImVec2(windowSize.x / (width + 1), windowSize.y / (height + 1) );
        padding = ImVec2(squareSize.x/2 + windowPos.x , squareSize.y/2 + windowPos.y);
        texture_id = CreateBackgroundTexture(Application::instance()->getRenderer(), squareSize,  windowSize.x, windowSize.y);
    }

    GridEntityManager::GridEntityManager(int height, int width) : GridEntityManager(height, width, ImVec2(720, 720), ImVec2(280, 40)) {}
    GridEntityManager::~GridEntityManager()
    {
        textureVector.destroy();
    }

    void GridEntityManager::setTextureVector(const TextureVector& textureVector)
    {
        this->textureVector = textureVector;
    }

    void GridEntityManager::renderOn(const Coordinate& pos, const int& textureId)
    {
        imgMap[pos] = GridImg(squareSize, absolutePosition(pos), textureVector[textureId]);
    }

    void GridEntityManager::setMoveTarget(const Coordinate& from, const Coordinate& to)
    {
        imgMap[to].enableMovement(absolutePosition(from));
    }

    void GridEntityManager::clearPos(const Coordinate& pos)
    {
        imgMap.erase(pos);
    }

    void GridEntityManager::renderGrid()
    {
        for (const auto& pair : imgMap) {
            pair.second.render();
        }
    }

    ImVec2 GridEntityManager::absolutePosition(const Coordinate& pos) const
    {
        return ImVec2(padding.x + pos.x * squareSize.x, padding.y + pos.y * squareSize.y);
    }

    Coordinate GridEntityManager::gridPosition(const ImVec2& pos) const
    {
        return Coordinate();
    }
}

