#include "ShapeType.hpp"
#include "Coordinate.hpp"
#include "Application.hpp"

std::map<std::tuple<ImVec4, float>, std::shared_ptr<ColorShapeType>, CompareTuple> ColorShapeTypeFactory::colorShapeCache = {};


void ColorShapeType::draw(const ImVec2& center) 
{
    if (ImGui::IsMouseClicked(0))
    {
        ImVec2 mousePos = ImGui::GetMousePos();

        bool withinXBounds = mousePos.x > center.x - size_/2 && mousePos.x < center.x + size_/2;
        bool withinYBounds = mousePos.y > center.y - size_/2 && mousePos.y < center.y + size_/2;

        if (withinXBounds && withinYBounds)
        {
            int xpos = (center.x - 370)/90;
            auto pos = Coordinate(xpos, 0);
            blink2dgui::Application::instance()->getGui().clicked(pos);
        }
    }
    
    ImVec2 topLeft = ImVec2(center.x - size_/2, center.y - size_/2);
    ImVec2 bottomRight = ImVec2(center.x + size_/2, center.y + size_/2);
    
    ImU32 imColor = IM_COL32((int)(color_.x * 255.0f), (int)(color_.y * 255.0f), (int)(color_.z * 255.0f), (int)(color_.w * 255.0f));
    
    // Fetch draw list
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Draw filled square
    drawList->AddRectFilled(topLeft, bottomRight, imColor);

        // Draw border (gridline) for the square
    //ImU32 borderColor = IM_COL32(50, 50, 50, 255);  // White color for the border
    //drawList->AddRect(topLeft, ImVec2(topLeft.x + size_, topLeft.y + size_), borderColor, 0.0f, ImDrawFlags_None, 0.01f);    
}