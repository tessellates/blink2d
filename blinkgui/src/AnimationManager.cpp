#include "AnimationManager.hpp"
#include "Application.hpp"

void AnimationManager::update()
{
    elapsedTime += blink2dgui::Application::activeGameClock().getDeltaTime();
    frameDuration = blink2dgui::Application::activeGameClock().getGameSpeed()/framesPerTick;
    if (elapsedTime >= frameDuration) 
    {
        elapsedTime -= frameDuration;
        currentFrame++;
    }
}