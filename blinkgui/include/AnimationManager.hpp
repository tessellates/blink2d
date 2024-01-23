#pragma once

class AnimationManager
{
public:
    AnimationManager() = default;

    int currentFrame = 0;
    float elapsedTime = 0;
    float framesPerTick = 8;
    float frameDuration = 0;

    void update();
};