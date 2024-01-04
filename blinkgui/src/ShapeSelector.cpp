#include "ShapeSelector.hpp"
#include "Application.hpp"

namespace blink2dgui
{
    ShapeSelector::ShapeSelector() 
    {
    }

    ShapeSelector::~ShapeSelector()
    {
    }

    void ShapeSelector::renderWindow()
    {
        ImGuiWindowFlags flags =  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
        ImVec2 windowSize = ImVec2(280, 720);  // Example size
        ImVec2 pos = ImVec2(0, 40);  // Example size
        ImVec2 pos2 = ImVec2(1000, 40);  // Example size
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(pos);

        ImGui::Begin("Game Settings", nullptr, flags);

        //const char* shapes[] = { "Square", "Hexagon" };
        //ImGui::Combo("Shapes", &currentShape_, shapes, IM_ARRAYSIZE(shapes));

        if(ImGui::SliderInt("Game Speed", &gameSpeed, 25, 1000))
        {
            Application::instance()->changeGameSpeed(gameSpeed);
        }

        // Create a slider from 5 to 300
        ImGui::SliderInt("Grid Size", &gridSize, 4, 40);

        // Add some spacing
        ImGui::Spacing();

        // Confirm button
        if (ImGui::Button("Confirm")) {
            // Handle the confirmation action
            // This is where you'd put code to use the selected grid size
            if (Application::instance()->gui_)
                Application::instance()->getGui().setGrid(gridSize);
        }

        const char* items[] = { "None", "Snake", "Connect", "Rocksolid" };
        ImGui::Combo("Game", &selectedItem, items, IM_ARRAYSIZE(items));

        ImGui::Spacing();

        // Confirm button
        if (ImGui::Button("Confirm##game")) {
            Application::instance()->init(selectedItem);
        }

        if (Application::instance()->gui_)
            ImGui::Text("FPS: %.3f", 1.0f / Application::instance()->getGui().gameClock.getDeltaTime() * 1000);

        ImGui::End();
/*
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(pos2);

        ImGui::Begin("Shape Selector mirror", nullptr, flags);
        ImGui::Combo("Shapes", &currentShape_, shapes, IM_ARRAYSIZE(shapes));

        ImGui::End();*/
    }
}
