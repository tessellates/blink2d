/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "GridLayer.hpp"
#include "Application.hpp"
#include "BackgroundTexture.hpp"

namespace blink2dgui
{
    GridLayer::GridLayer( const std::function<ImVec2(Coordinate)>& conversionFunction, const ImVec2& windowSize, const ImVec2& squareSize) : absolutePosition(conversionFunction), windowSize(windowSize), squareSize(squareSize)
    {}

    GridLayer::~GridLayer()
    {

    }

    void GridLayer::defaultInit()
    {
        std::vector<BlinkTexture> tv;
        tv.push_back(BlinkTexture(CreateBackgroundTexture(Application::instance()->getRenderer(), squareSize.x, windowSize.y, windowSize.x)));
        addBackgroundTextures(tv);
    }

    void GridLayer::setTextureVector(const std::vector<BlinkTexture>& textureVector)
    {
        this->textureVector = std::move(textureVector);
    }

    void GridLayer::addBackgroundTextures(const std::vector<BlinkTexture>& textureVector)
    {
        backgroundTextures = std::vector<GridImg>();
        for (const auto& texture : textureVector)
        {
            backgroundTextures.push_back(GridImg(windowSize, absolutePosition(Coordinate{0,0}) - squareSize/2, texture));
        }
    }

    void GridLayer::renderOn(const Coordinate& pos, const int& textureId)
    {
        imgMap[pos] = GridImg(squareSize, absolutePosition(pos), textureVector[textureId]);
    }

    void GridLayer::setMoveTarget(const Coordinate& from, const Coordinate& to, const bool& defaultAction)
    {
        imgMap[to].enableMovement(absolutePosition(from), defaultAction);
    }

    void GridLayer::clearPos(const Coordinate& pos)
    {
        imgMap.erase(pos);
    }

    void GridLayer::renderGrid()
    {
        for(auto& texture : backgroundTextures)
        {
            texture.render();
        }

        for (auto& pair : imgMap) 
        {
            pair.second.render();
        }
    }
}

