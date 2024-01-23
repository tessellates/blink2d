
#include "GemFallGame.hpp"
#include "Application.hpp"

void GemFallGame::init(const GameParameters& parameters)
{
    windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    padding = ImVec2(20, 20);
    int base = 10;
    this->parameters = parameters;
    ImVec2 guiSpace = parameters.gameSpace - padding * 2;
    ImVec2 guiLocation = parameters.gameRoot + padding;
    gemFallGui.init(guiLocation, guiSpace, base);
    gemFallModel = GemFallModel(base);

    gemFallModel.addGem.push_back([&](const Coordinate& p) {this->gemFallGui.addGem(p);});
    gemFallModel.removePiece.push_back([&](const Coordinate& p) {this->gemFallGui.remove(p);});
    gemFallModel.addSpawn.push_back([&](const Coordinate& p) {this->gemFallGui.addSpawn(p);});
    gemFallModel.permGem.push_back([&](const Coordinate& p) {this->gemFallGui.permGem(p);});
}

void GemFallGame::clicked(const ImVec2& position, int id)
{
    if (gemFallGui.isInGui(position) && play)
    {
        play = false;
        gemFallModel.resetCycle();
        gemFallModel.play(gemFallGui.builder.gridPosition(position));
        play = true;
    }
}

void GemFallGame::hover(const ImVec2& position, int id)
{
    /*
    if (GemFallGui.isInGui(position) && play)
    {
        if (currentPreview != GemFallGui.builder.gridPosition(position).x)
        {
            GemFallModel.resetCycle();
            currentPreview = GemFallGui.builder.gridPosition(position).x;
            GemFallGui.previewMode = true;
            GemFallModel.preview(GemFallGui.builder.gridPosition(position).x);
            GemFallGui.previewMode = false;
        }
    }
    else
    {
        GemFallModel.resetCycle();
    }*/
}

void GemFallGame::renderImGui()
{
    ImGui::SetNextWindowSize(parameters.gameSpace);
    ImGui::SetNextWindowPos(parameters.gameRoot);

    ImGuiStyle originalStyle = ImGui::GetStyle();

    // Modify the style for a specific window
    ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

    ImGui::Begin("GemFall Game", nullptr, windowFlags);

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

    ImGui::End();
    ImGui::GetStyle() = originalStyle;
}

void GemFallGame::updateSDL()
{
    clock.update();
    if (clock.getIntervalProgress() >= 1) {
        gemFallGui.gems.clear();
        gemFallModel.tick();
    }
    gemFallGui.updateVisuals(0);
    gemFallGui.updateSDL();
}


void GemFallGame::forward()
{
    gemFallModel.forward();
}

void GemFallGame::backward()
{
    gemFallModel.backward();
}
   