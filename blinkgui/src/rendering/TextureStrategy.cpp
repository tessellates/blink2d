#include "TextureStrategy.hpp"
#include "Application.hpp"

void ITextureStrategy::update() {}

StaticTextureStrategy::StaticTextureStrategy(const BlinkTexture& texture) : texture(texture) {}
const BlinkTexture* StaticTextureStrategy::getTexture() const {return &texture;}
AnimatedTextureStrategy::AnimatedTextureStrategy(const std::vector<BlinkTexture>& frames, float frameRate) : frames(frames), frameRate(frameRate), currentFrame(0) {}

const BlinkTexture* AnimatedTextureStrategy::getTexture() const {
    // Update currentFrame based on frameRate and time logic
    return &frames[currentFrame];
}

SingleLoopTextureStrategy::SingleLoopTextureStrategy(const std::vector<BlinkTexture>& frames, AnimationManager* manager) : frames(frames), manager(manager), currentFrame(0), startFrame(manager->currentFrame) {
}

const BlinkTexture* SingleLoopTextureStrategy::getTexture() const 
{
    if (currentFrame >= frames.size())
    {
        return nullptr;
    }
    return &frames[currentFrame];
}

void SingleLoopTextureStrategy::update()
{
    currentFrame = manager->currentFrame - startFrame;
}