#pragma once

#include "BlinkGame.hpp"
#include "ConnectGui.hpp"
#include "ConnectModel.hpp"

class ConnectGame : public BlinkGame
{
public:
    ConnectGame() = default;
    ~ConnectGame() = default;
    void init(const GameParameters& parameters) override;

    void clicked(const ImVec2& position, int id = 0);
    void hover(const ImVec2& position, int id = 0);

    void renderImGui() override; // renders the imgui parts of the game
    void updateSDL() override; // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)
    
    void forward() override;
    void backward() override;

    ImGuiWindowFlags windowFlags;
    
    ConnectGui connectGui;
    ConnectModel connectModel;
    bool play = true;

    ImVec2 padding;
    bool isHoverActive = false; // State variable to control hover
    int currentPreview = -1;
};