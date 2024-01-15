
#include "ConnectGame.hpp"
#include "Application.hpp"

void ConnectGame::init(const GameParameters& parameters)
{
    windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    padding = ImVec2(20, 20);
    this->parameters = parameters;
    ImVec2 guiSpace = parameters.gameSpace - padding * 2;
    ImVec2 guiLocation = parameters.gameRoot + padding;
    connectGui.init(guiLocation, guiSpace);
    connectModel = ConnectModel();
    connectModel.addConnectEntity.push_back([&](const Coordinate& p, int c) {this->connectGui.addConnectEntity(p, c);});
    connectModel.removeConnectEntity.push_back([&](const Coordinate& p) {this->connectGui.removeConnectEntity(p);});
    connectModel.changeConnectEntity.push_back([&](const Coordinate& p, int c) {this->connectGui.changeConnectEntity(p, c);});
}

void ConnectGame::clicked(const ImVec2& position, int id)
{
    if (connectGui.isInGui(position) && play)
    {
        play = false;
        resetCycle();
        connectModel.play(connectGui.builder.gridPosition(position).x);
        currentPreview = -1;
        play = true;
    }
}

void ConnectGame::hover(const ImVec2& position, int id)
{
    if (connectGui.isInGui(position) && play)
    {
        if (currentPreview != connectGui.builder.gridPosition(position).x)
        {
            connectModel.resetCycle();
            currentPreview = connectGui.builder.gridPosition(position).x;
            connectGui.previewMode = true;
            connectModel.preview(connectGui.builder.gridPosition(position).x);
            connectGui.previewMode = false;
        }
    }
    else
    {
        connectModel.resetCycle();
    }
}

void ConnectGame::renderImGui()
{
    ImGui::SetNextWindowSize(parameters.gameSpace);
    ImGui::SetNextWindowPos(parameters.gameRoot);

    ImGuiStyle originalStyle = ImGui::GetStyle();

    // Modify the style for a specific window
    ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

    ImGui::Begin("Connect Game", nullptr, windowFlags);

    //ImGui::Image()
    // Check for mouse click inside the window
    if (ImGui::IsWindowHovered()) 
    {
        ImVec2 mousePos = ImGui::GetMousePos(); // Get mouse position in screen coordinates
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            clicked(mousePos);
            isHoverActive = false; 
        }
        else
        {
            if (!isHoverActive)
            {
                isHoverActive = true;
                hover(mousePos);
                isHoverActive = false;
            }
        }
    }
    else 
    {
        if (!isHoverActive)
        {
            isHoverActive = true;
            hover({0,0});
            isHoverActive = false;
        }
    }

    //SDL_SetRenderDrawColor(blink2dgui::Application::instance()->getRenderer(), 0, 0, 0, 255); // Set the clear color
    //SDL_RenderClear(blink2dgui::Application::instance()->getRenderer());

    ImGui::End();
    ImGui::GetStyle() = originalStyle;
}

void ConnectGame::updateSDL()
{
    clock.update();
    connectGui.updateSDL();
    for (auto& [key, value] : connectGui.visualEntityMap) {
        value.render();
    }
}


void ConnectGame::forward()
{
    connectModel.forward();
}

void ConnectGame::backward()
{
    connectModel.backward();
}
   