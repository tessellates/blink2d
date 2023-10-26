#pragma once
#include "imgui.h"
#include <iostream>
#include <functional>

inline bool drawShapeWithHover(
    std::function<void(const ImVec2&, float, const ImU32&)> drawFunc, 
    const ImVec2& pos, 
    float size,
    const ImU32& color, 
    const ImU32& hoverColor)
{
    bool clicked = false;
    ImGui::SetCursorScreenPos(pos);
    ImGui::InvisibleButton("button", ImVec2(size, size));
    if (ImGui::IsItemClicked()) {
        clicked = true;
    }
    ImU32 currentColor = ImGui::IsItemHovered() ? hoverColor : color;
    drawFunc(pos, size, currentColor);
    return clicked;
};

inline void drawTriangle(const ImVec2& pos, float size, const ImU32& color) {
    auto drawList = ImGui::GetWindowDrawList();
    float halfSize = size / 2.0f;
    drawList->AddTriangleFilled(
        ImVec2(pos.x, pos.y + halfSize),  // Bottom left point
        ImVec2(pos.x + size*0.86602540378, pos.y),  // Right point
        ImVec2(pos.x + size*0.86602540378, pos.y + size),  // Bottom right point
        color);
};

inline void drawInverseTriangle(const ImVec2& pos, float size, const ImU32& color) {
    auto drawList = ImGui::GetWindowDrawList();
    float halfSize = size / 2.0f;
    drawList->AddTriangleFilled(
        ImVec2(pos.x, pos.y),  // Left point
        ImVec2(pos.x + size*0.86602540378, pos.y + halfSize),  // Bottom right point
        ImVec2(pos.x, pos.y + size),  // Bottom left point
        color);
}

inline void drawSquare(const ImVec2& pos, float size, const ImU32& color) {
    auto drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(pos, ImVec2(pos.x + size, pos.y + size), color);
}

inline void drawTwoVerticalLines(const ImVec2& pos, float size, const ImU32& color) {
    auto drawList = ImGui::GetWindowDrawList();
    float thirdSize = size / 3.0f;
    drawList->AddLine(ImVec2(pos.x + thirdSize, pos.y), ImVec2(pos.x + thirdSize, pos.y + size), color, 3.0);
    drawList->AddLine(ImVec2(pos.x + 2 * thirdSize, pos.y), ImVec2(pos.x + 2 * thirdSize, pos.y + size), color, 3.0);
};

inline void drawLongTriangleLeft(const ImVec2& pos, float size, const ImU32& color) {
    float halfSize = size / 2.0f;

    // You need to define how "long" affects the triangle's shape. Here's a simple example:
    auto drawList = ImGui::GetWindowDrawList();
    drawList->AddTriangleFilled(
        ImVec2(pos.x, pos.y + halfSize),  // Bottom left point
        ImVec2(pos.x + size, pos.y + size*0.10 ),  // Right point
        ImVec2(pos.x + size, pos.y + size*0.90),  // Bottom right point
        color);
};

inline void drawLongTriangleRight(const ImVec2& pos, float size, const
 ImU32& color) {
    float halfSize = size / 2.0f;

    // Similar to the left, but you'll need to adjust the coordinates accordingly.
    auto drawList = ImGui::GetWindowDrawList();
    drawList->AddTriangleFilled(
        ImVec2(pos.x, pos.y + size*0.10),  // Left point
        ImVec2(pos.x + size, pos.y + halfSize),  // Bottom right point
        ImVec2(pos.x, pos.y + size*0.90),  // Bottom left point
        color);
};

