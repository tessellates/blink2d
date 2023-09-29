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
        ImVec2 windowSize = ImVec2(280, 720);  // Example size
        ImGui::Begin("Shape Selector");

        const char* shapes[] = { "Square", "Hexagon" };
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
