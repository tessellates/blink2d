
#include "NoitaSimGame.hpp"
#include "Application.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time


void NoitaSimGame::init(const GameParameters& parameters)
{
    windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    padding = ImVec2(0, 0);
    this->parameters = parameters;
    ImVec2 guiSpace = parameters.gameSpace - padding * 2;
    ImVec2 guiLocation = parameters.gameRoot + padding;
    noitaSimGui.init(guiLocation.x, guiLocation.y, guiSpace.x, guiSpace.y);
    cpanel = NoitaControlPanel(parameters.panelSpace, parameters.panelRoot);

    std::cout << ">WELCOME<" << std::endl;
    std::cout << "MAX PARTICLES:" << NoitaConfig::numCells << std::endl;
}

void NoitaSimGame::mouseDown(const ImVec2& position)
{
    mouseDownCoordinate(noitaSimGui.gridLocation(position.x, position.y));
    for (int i = 1; i < brushSize; ++i)
    {
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x+i, position.y));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x-i, position.y));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x, position.y+i));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x, position.y-i));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x+i, position.y+i));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x-i, position.y-i));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x+i, position.y-i));
        mouseDownCoordinate(noitaSimGui.gridLocation(position.x-i, position.y+i));
    }

}

void NoitaSimGame::mouseDownCoordinate(const Coordinate& coordinate)
{
    if (noitaSimGui.inGrid(coordinate))
    {
        //noitaState.setSand(coordinate.x, coordinate.y);
    }
}



void NoitaSimGame::clicked(const ImVec2& position, int id)
{

}

void NoitaSimGame::hover(const ImVec2& position, int id)
{

}

void NoitaSimGame::renderImGui()
{
    cpanel.render(cm, brushSize);
    ImGui::SetNextWindowSize(parameters.gameSpace);
    ImGui::SetNextWindowPos(parameters.gameRoot);

    ImGuiStyle originalStyle = ImGui::GetStyle();

    // Modify the style for a specific window
    ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

    ImGui::Begin("NoitaSim Game", nullptr, windowFlags);

    if (ImGui::IsWindowHovered()) 
    {
        ImVec2 mousePos = ImGui::GetMousePos(); // Get mouse position in screen coordinates
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            //mouseDown(mousePos);
        }
        
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            if (wasDown)
            {
                float minX = std::min(oldPos.x, mousePos.x);
                float maxX = std::max(oldPos.x, mousePos.x);
                float minY = std::min(oldPos.y, mousePos.y);
                float maxY = std::max(oldPos.y, mousePos.y);
                for (float y = minY; y <= maxY; ++y) {
                    for (float x = minX; x <= maxX; ++x) {
                        mouseDown({x, y});
                    }
                }
                oldPos = mousePos;
            }
            else
            {
                mouseDown(mousePos);
                wasDown = true;
                oldPos = mousePos;
            }
        }
        else
        {
            wasDown = false;
        }
    }

    ImGui::End();
    ImGui::GetStyle() = originalStyle;
}

void NoitaSimGame::updateSDL()
{
    clock.update();
    updateGame();
    noitaSimGui.updateSDL();
}

void NoitaSimGame::updateGame()
{
    total.timeStart();
    walk.timeStart();
    cm.updateMove();
    walk.timeEnd();
    move.timeStart();
    cm.updateCells();
    move.timeEnd();
    render.timeStart();
    noitaSimGui.updatePixelData(cm.cells);
    render.timeEnd();
    total.timeEnd();
    //noitaState.random_updater_simple();
    {
        //noitaSimGui.updatePixelData(noitaState.simpleCells);
        return;
    }
    /*
    //noitaState.random_updater_single();

    //noitaState.random_updater();
    noitaState.update();
    if (noitaState.odd)
    {
        noitaSimGui.updatePixelData(noitaState.cells);
    }
    else
    {
        noitaSimGui.updatePixelData(noitaState.cellsOdd);
    }*/
}

void NoitaSimGame::forward()
{
   //NoitaSimModel.forward();
}

void NoitaSimGame::backward()
{
    //NoitaSimModel.backward();
}
   