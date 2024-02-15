#pragma once

#include "BlinkTexture.hpp"
#include "AnimationManager.hpp"

#include <vector>

class ITextureStrategy {
public:
    virtual ~ITextureStrategy() = default;
    virtual const BlinkTexture* getTexture() const = 0;
    virtual void update();
};

using TextureStrategyPtr = std::unique_ptr<ITextureStrategy>;

class StaticTextureStrategy : public ITextureStrategy {
private:
    BlinkTexture texture;

public:
    StaticTextureStrategy(const BlinkTexture& texture);
    const BlinkTexture* getTexture() const override; 
};

using StaticTextureStrategyPtr = std::unique_ptr<StaticTextureStrategy>;

class AnimatedTextureStrategy : public ITextureStrategy {
private:
    std::vector<BlinkTexture> frames;
    float frameRate;
    int currentFrame;

public:
    AnimatedTextureStrategy(const std::vector<BlinkTexture>& frames, float frameRate);
    const BlinkTexture* getTexture() const override; 
};

class SingleLoopTextureStrategy : public ITextureStrategy {
private:
    std::vector<BlinkTexture> frames;
    AnimationManager* manager;
    int startFrame;
    int currentFrame;

public:
    SingleLoopTextureStrategy(const std::vector<BlinkTexture>& frames, AnimationManager* manager);
    void update() override;
    const BlinkTexture* getTexture() const override; 
};