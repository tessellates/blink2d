#pragma once

#include "BlinkGame.hpp"
//#include "NoitaSimGui.hpp"
#include "RenderExManager.hpp"
#include "ColorTextureManager.hpp"
#include "FastTexture.hpp"
//#include "NoitaSimModel.hpp"

class NoitaSimGame : public BlinkGame
{
public:
    NoitaSimGame() = default;
    ~NoitaSimGame() = default;
    void init(const GameParameters& parameters) override;

    void clicked(const ImVec2& position, int id = 0);
    void hover(const ImVec2& position, int id = 0);

    void renderImGui() override; // renders the imgui parts of the game
    void updateSDL() override; // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)
    
    void forward() override;
    void backward() override;

    void updateGame();

    ImGuiWindowFlags windowFlags;
    
    //NoitaSimGui NoitaSimGui;
    //NoitaSimModel NoitaSimModel;
    bool play = true;
    ImVec2 padding;
    bool isHoverActive = false; // State variable to control hover
    FastTexture<1312, 945> fastTexture;
    std::array<Uint32, 20> sdl_colors;

};