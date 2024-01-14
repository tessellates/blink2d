#pragma once

#include "BlinkGame.hpp"

class RockSolidGame : public BlinkGame
{
public:
    RockSolidGame() = default;
    ~RockSolidGame() = default;
    virtual void init(const GameParameters& parameters);

    void clicked(const ImVec2& position, int id = 0);

    void renderImGui(); // renders the imgui parts of the game
    void updateSDL(); // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)
    
    RockSolidGui rockSolidGui;
    RockSolidModel rockSolidModel;
    
    RockSolidToolGui rockSolidToolGui;
    ActiveToolModel activeToolModel;
};