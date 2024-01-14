/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "GridEntityManager.hpp"
#include "Application.hpp"
#include "BackgroundTexture.hpp"

namespace blink2dgui
{

    GridEntityManager::GridEntityManager(int width, int height, const ImVec2& windowSize, const ImVec2& windowPos) : width(width), height(height), windowSize(windowSize), windowPos(windowPos) 
    {
        windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
        squareSize = ImVec2(windowSize.x / (width + 1), windowSize.y / (height + 1) );
        padding = ImVec2(squareSize.x/2 , squareSize.y/2);
        boardSize = ImVec2(windowSize.x - squareSize.x/2 , windowSize.y - squareSize.y/2);
    }

    GridEntityManager::GridEntityManager(int height, int width) : GridEntityManager(height, width, ImVec2(720, 720), ImVec2(280, 40)) {}

    GridEntityManager::GridEntityManager()
    {

    }

    GridEntityManager::~GridEntityManager()
    {

    }

    GridLayer& GridEntityManager::getLayer(int i)
    {
        while (i >= layers.size())
        {
            layers.push_back(GridLayer{[&](const Coordinate& pos){ return this->absolutePosition(pos); }, windowSize, squareSize});
        }
        return layers[i];
    }


    void GridEntityManager::renderGrid()
    {
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos);

        ImGuiStyle originalStyle = ImGui::GetStyle();

        // Modify the style for a specific window
        ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

        ImGui::Begin("Square Grid", nullptr, windowFlags);


        //ImGui::Image()
        // Check for mouse click inside the window
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) {
            ImVec2 mousePos = ImGui::GetMousePos(); // Get mouse position in screen coordinates
            ImVec2 clickPosInWindow = ImVec2(mousePos.x - windowPos.x, mousePos.y - windowPos.y);
            if (clickPosInWindow.x >= padding.x && clickPosInWindow.x < windowSize.x - padding.x && clickPosInWindow.y >= padding.y && clickPosInWindow.y < windowSize.y - padding.y)
            {
                //blink2dgui::Application::instance()->getGui().clicked(gridPosition(clickPosInWindow));
            }
        }

        SDL_SetRenderDrawColor(Application::instance()->getRenderer(), 0, 0, 0, 255); // Set the clear color
        SDL_RenderClear(Application::instance()->getRenderer());

        ImGui::End();
        ImGui::GetStyle() = originalStyle;

    }

    void GridEntityManager::renderSDL()
    {
        for (auto& layer : layers) 
        {
            layer.renderGrid();
        }
        
        for (auto& [key, val] : visualEntityMap)
        {
            val.render();
        }

    }

    ImVec2 GridEntityManager::absolutePosition(const Coordinate& pos) const
    {
 
        return ImVec2(windowPos.x + padding.x + pos.x * squareSize.x, windowPos.y + padding.y + pos.y * squareSize.y);
    }

    ImVec2 GridEntityManager::relativePosition(const Coordinate& pos) const
    {
        return ImVec2(padding.x + pos.x * squareSize.x, padding.y + pos.y * squareSize.y);
    }

    Coordinate GridEntityManager::gridPosition(const ImVec2& pos) const
    {
        int x = (pos.x - padding.x) / squareSize.x;
        int y = (pos.y - padding.y) / squareSize.y;
        return Coordinate(x, y);
    }
}

