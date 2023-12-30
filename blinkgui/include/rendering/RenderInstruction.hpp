#pragma once

#include <memory>
#include <optional>

#include "Transform.hpp"
#include "TextureStrategy.hpp"
#include "TransformStrategy.hpp"

class RenderInstruction
{
public:
    RenderInstruction() = default;
    RenderInstruction(std::unique_ptr<ITextureStrategy> strategy, int layer = 0);

    RenderInstruction(const RenderInstruction&) = delete;
    RenderInstruction& operator=(const RenderInstruction&) = delete;

    RenderInstruction(RenderInstruction&&) = default;
    RenderInstruction& operator=(RenderInstruction&&) = default;

    void render(const Transform& transform);
    void setTextureStrategy(std::unique_ptr<ITextureStrategy> strategy);
    int layer;
    Transform relativeTransform;
    
    std::optional<MoveStrategy> ms;
private:
    std::unique_ptr<ITextureStrategy> textureStrategy;
};

