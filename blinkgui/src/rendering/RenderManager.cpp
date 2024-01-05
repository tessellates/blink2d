
#include "rendering/RenderManager.hpp"

void RenderManager::renderSDL()
{
    for (auto& baseAction : baseLayer)
    {
        baseAction.render();
    }
    baseLayer.clear();

    for (auto& layer : layers)
    {
        for (auto& action : layer)
        {
            action.render();
        }
        layer.clear();
    }
}

void RenderManager::addRenderAction(const BlinkTexture& texture, int x, int y, int layerID) 
{
    if (layerID == -1)
    {
        baseLayer.emplace_back(x, y, texture);
        return;
    }
    layers[layerID].emplace_back(x, y, texture);
}

void RenderManager::addRenderAction(const Transform& transform, const BlinkTexture& texture, int layerID)
{
    if (layerID == -1)
    {
        baseLayer.emplace_back(transform, texture);
        return;
    }
    layers[layerID].emplace_back(transform, texture);
}