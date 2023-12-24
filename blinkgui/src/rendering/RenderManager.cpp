
#include "RenderManager.hpp"

void RenderManager::renderSDL()
{
    for (const auto& layer : layers)
    {
        for (const auto& action : layer)
        {
            action.render();
        }
    }
}

void addRenderAction(const BlinkTexture& texture, int x, int y, int layerID) 
{
    layers[layerID].emplace_back(texture, x, y);
}