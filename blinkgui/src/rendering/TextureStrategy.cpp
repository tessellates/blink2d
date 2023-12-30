#include "TextureStrategy.hpp"


StaticTextureStrategy::StaticTextureStrategy(const BlinkTexture& texture) : texture(texture) {}
const BlinkTexture& StaticTextureStrategy::getTexture() const {return texture;}
AnimatedTextureStrategy::AnimatedTextureStrategy(const std::vector<BlinkTexture>& frames, float frameRate) : frames(frames), frameRate(frameRate), currentFrame(0) {}

const BlinkTexture& AnimatedTextureStrategy::getTexture() const {
    // Update currentFrame based on frameRate and time logic
    return frames[currentFrame];
}
