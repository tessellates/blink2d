#include "BlinkGame.hpp"
#include "GameClock.hpp"

void BlinkGame::init(const GameParameters& parameters)
{
    this->parameters = parameters;
}

void BlinkGame::renderImGui()
{

}

void BlinkGame::updateSDL()
{

}

void BlinkGame::forward()
{

}

void BlinkGame::backward()
{

}
    
GameClock& BlinkGame::getClock()
{
    return clock;
}

const GameClock& BlinkGame::getClock() const
{
    return clock;
}

const GameSettings& BlinkGame::getGameSettings() const
{
    return settings;
}
