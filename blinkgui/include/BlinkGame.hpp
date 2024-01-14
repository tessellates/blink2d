#pragma once

#include "GameParameters.hpp"
#include "GameClock.hpp"
#include "GameSettings.hpp"

class BlinkGame
{
public:
    BlinkGame() = default;
    virtual ~BlinkGame() = default;
    virtual void init(const GameParameters& parameters);

    void clicked(const ImVec2& position, int id = 0);

    virtual void renderImGui(); // renders the imgui parts of the game
    virtual void updateSDL(); // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)

    virtual void forward();
    virtual void backward();
    
    GameClock& getClock();
    const GameClock& getClock() const;

    const GameSettings& getGameSettings() const;
    
protected:
    GameSettings settings;
    GameParameters parameters;
    GameClock clock; // master clock
};