
#include "rendering/RenderInstruction.hpp"
#include "rendering/RenderManager.hpp"
#include <iostream>

RenderInstruction::RenderInstruction(std::unique_ptr<ITextureStrategy> strategy, int layer) : textureStrategy(std::move(strategy)), layer(layer)
{
}

void RenderInstruction::render(const Transform& transform)
{
    if (ms)
    {
        if(!(*ms).update(relativeTransform))
        {
            ms.reset();
        }
    }
    if (textureStrategy)
    {
        textureStrategy->update();
    }
    if (!isDead())
    {
        RenderManager::instance()->addRenderAction(transform+relativeTransform, *textureStrategy->getTexture(), layer);
    }
}

void RenderInstruction::setTextureStrategy(std::unique_ptr<ITextureStrategy> strategy)
{
    textureStrategy = std::move(strategy);
}

bool RenderInstruction::isDead() const
{
    if (textureStrategy)
    {
        if (textureStrategy->getTexture() == nullptr)
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    return false;
}
