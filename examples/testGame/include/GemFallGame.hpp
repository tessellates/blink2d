#pragma once

#include "BlinkGame.hpp"
#include "GemFallGui.hpp"
#include "GemFallModel.hpp"

class GemFallGame : public BlinkGame
{
public:
    GemFallGame() = default;
    ~GemFallGame() = default;
    void init(const GameParameters& parameters) override;

    void clicked(const ImVec2& position, int id = 0);
    void hover(const ImVec2& position, int id = 0);

    void renderImGui() override; // renders the imgui parts of the game
    void updateSDL() override; // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)
    
    void forward() override;
    void backward() override;

    ImGuiWindowFlags windowFlags;
    
    GemFallGui gemFallGui;
    GemFallModel gemFallModel;
    bool play = true;

    ImVec2 padding;
    bool isHoverActive = false; // State variable to control hover
    int currentPreview = -1;

    float elapsedTime = 0;
};