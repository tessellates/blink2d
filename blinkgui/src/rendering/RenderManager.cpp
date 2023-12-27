
#include "RenderManager.hpp"

void RenderManager::renderSDL()
{
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
    layers[layerID].emplace_back(x, y, texture);
}