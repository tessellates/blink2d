#pragma once

#include "BlinkGame.hpp"
#include "NoitaSimGui.hpp"
#include "CellManager.hpp"
#include "RenderExManager.hpp"
#include "ColorTextureManager.hpp"
#include "NoitaControlPanel.hpp"
#include "SDLTimer.hpp"

class NoitaSimGame : public BlinkGame
{
public:
    NoitaSimGame() = default;
    ~NoitaSimGame() = default;
    void init(const GameParameters& parameters) override;

    void mouseDown(const ImVec2& position);
    void mouseDownCoordinate(const Coordinate&);
    void clicked(const ImVec2& position, int id = 0);
    void hover(const ImVec2& position, int id = 0);

    void renderImGui() override; // renders the imgui parts of the game
    void updateSDL() override; // updates the SDL instructions that are part of the game (the rendering itself is triggered in the application class)
    
    void forward() override;
    void backward() override;

    void updateGame();

    ImGuiWindowFlags windowFlags;
    
    NoitaSimGui noitaSimGui;
    NoitaControlPanel cpanel;
    CellManager cm;
    
    //NoitaSimModel NoitaSimModel;
    bool play = true;
    ImVec2 padding;
    bool isHoverActive = false; // State variable to control hover
    bool wasDown = false;
    ImVec2 oldPos;

    int brushSize = 2;

    SDLTimer walk{"------walk-------"};
    SDLTimer move{"move"};
    SDLTimer render{"render"};
    SDLTimer total{"------total------"};

};