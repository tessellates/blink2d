#include "BlinkGame.hpp"
#include "GameClock.hpp"

void BlinkGame::init(const GameParameters& parameters)
{
    this->parameters = parameters;
}

void BlinkGame::clicked(const ImVec2& position, int id)
{

}

void BlinkGame::renderImGui()
{

}

void BlinkGame::updateSDL()
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
