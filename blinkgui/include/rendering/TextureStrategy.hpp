#pragma once

#include "BlinkTexture.hpp"

class ITextureStrategy {
public:
    virtual ~ITextureStrategy() = default;
    virtual const BlinkTexture& getTexture() const = 0;
};

using TextureStrategyPtr = std::unique_ptr<ITextureStrategy>;

class StaticTextureStrategy : public ITextureStrategy {
private:
    BlinkTexture texture;

public:
    StaticTextureStrategy(const BlinkTexture& texture);
    const BlinkTexture& getTexture() const override; 
};

using StaticTextureStrategyPtr = std::unique_ptr<StaticTextureStrategy>;

class AnimatedTextureStrategy : public ITextureStrategy {
private:
    std::vector<BlinkTexture> frames;
    float frameRate;
    int currentFrame;

public:
    AnimatedTextureStrategy(const std::vector<BlinkTexture>& frames, float frameRate);
    const BlinkTexture& getTexture() const override; 
};