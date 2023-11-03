#include "GameClock.hpp"
#include <iostream>

GameClock::GameClock(float gameSpeed) : gameSpeed(gameSpeed) {
    lastTick = SDL_GetTicks();
    startTick = lastTick;
    intervalTick = lastTick;
    intervalTime = 0.0f;
    deltaTime = 0.0f;
}

void GameClock::setGameSpeed(float gameSpeed)
{
    this->gameSpeed = gameSpeed;
    intervalTick = SDL_GetTicks();
}

float GameClock::getIntervalProgress() const
{
    return intervalTime/gameSpeed;
}

void GameClock::update() {
    Uint32 currentTick = SDL_GetTicks();
    if (intervalTime >= gameSpeed)
    {
        intervalTick = currentTick;
    }
    deltaTime = (currentTick - lastTick);
    lastTick = currentTick;
    intervalTime = (currentTick - intervalTick);
}

float GameClock::getDeltaTime() const {
    return deltaTime;
}

float GameClock::getIntervalTime() const {
    return intervalTime;
}

Uint32 GameClock::getTotalTime() const {
    return lastTick - startTick;
}

