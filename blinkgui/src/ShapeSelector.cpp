#include "ShapeSelector.hpp"

namespace blink2dgui
{
    ShapeSelector::ShapeSelector() : currentShape_(0)
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

        ImGui::Begin("Shape Selector", nullptr, flags);

        const char* shapes[] = { "Square", "Hexagon" };
        ImGui::Combo("Shapes", &currentShape_, shapes, IM_ARRAYSIZE(shapes));


        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(pos2);

        ImGui::Begin("Shape Selector mirror", nullptr, flags);
        ImGui::Combo("Shapes", &currentShape_, shapes, IM_ARRAYSIZE(shapes));

        ImGui::End();
    }

    bool ShapeSelector::isSquareSelected() const
    {
        return currentShape_ == 0;
    }

    bool ShapeSelector::isHexagonSelected() const
    {
        return currentShape_ == 1;
    }
}
