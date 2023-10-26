#include "ControllerWindow.hpp"
#include "Buttons.hpp"
#include "Application.hpp"

namespace blink2dgui
{
    ControllerWindow::ControllerWindow() 
    {
    }

    ControllerWindow::~ControllerWindow()
    {
    }


// This function should be placed in your application's rendering loop.
void ControllerWindow::renderWindow()
{
    ImGuiWindowFlags flags =  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    int width = 1280;
    int height = 40;
    ImVec2 windowSize = ImVec2(width, height);
    ImVec2 pos = ImVec2(0, 0); 
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(pos);
    // Begin a new ImGui window called "Control Window"
    ImGui::Begin("Control Window", nullptr, flags);
    // We assume each icon is 20x20 pixels for this example. Adjust as needed.
    const float iconSize = 20.0f;

    float size = 22;
    pos = ImVec2(640 - size/2 , 10);

    ImU32 baseColor = IM_COL32(255, 255, 255, 255);
    ImU32 hoverColor = IM_COL32(100, 100, 255, 255);
    ImVec2 padding = ImVec2(40, 0);
    // Draw each shape with the hover effect.
    if (drawShapeWithHover(drawSquare, pos - padding * 2, size, baseColor, hoverColor))
    {
        std::cout << "RESET\n";
    }
    if (drawShapeWithHover(drawLongTriangleLeft, pos - padding, size, baseColor, hoverColor))
    {
        std::cout << "PREVIOUS\n";
    }
    if (drawShapeWithHover(drawLongTriangleRight, pos , size, baseColor, hoverColor))
    {
        std::cout << "NEXT\n";
    }
    if (drawShapeWithHover(drawTwoVerticalLines, pos + padding, size, baseColor, hoverColor))
    {
        std::cout << "PAUSE\n";
    }
    if (drawShapeWithHover(drawInverseTriangle, pos + padding * 2, size, baseColor, hoverColor))
    {
        std::cout << "PLAY\n";
    }

    // End the ImGui window
    ImGui::End();
}

}
