#pragma once

#include "imgui.h"
#include <random>

class ShapeType {
public:
    float size_ = 30;
    virtual void draw(const ImVec2& center) = 0;
    virtual ~ShapeType() = default;
    virtual std::unique_ptr<ShapeType> clone() const = 0;
};

class ColorShapeType : public ShapeType {
private:
    ImVec4 color_;
    
public:
    ColorShapeType(const ImVec4& color) : color_(color) {}

    virtual std::unique_ptr<ShapeType> clone() const override {
        return std::make_unique<ColorShapeType>(*this);
    }

    void draw(const ImVec2& center) override 
    {
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        // Generate random values for each component
        float r = dis(gen);
        float g = dis(gen);
        float b = dis(gen);
        float a = dis(gen);  // if you always want opaque colors, set this to 1.0f
        //color_ = ImVec4(r, g, b, a);
        if (ImGui::IsMouseClicked(0))
        {
            ImVec2 mousePos = ImGui::GetMousePos();

            bool withinXBounds = mousePos.x > center.x - size_/2 && mousePos.x < center.x + size_/2;
            bool withinYBounds = mousePos.y > center.y - size_/2 && mousePos.y < center.y + size_/2;

            if (withinXBounds && withinYBounds)
            {
                // Toggle color between black and yellow
                if (color_.x == 0)
                    color_ = ImVec4(0.5f, 0.5f, 0, 1); // Yellow
                else
                    color_ = ImVec4(0, 0, 0, 1); // Black
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
        ImU32 borderColor = IM_COL32(50, 50, 50, 255);  // White color for the border
        drawList->AddRect(topLeft, ImVec2(topLeft.x + size_, topLeft.y + size_), borderColor, 0.0f, ImDrawFlags_None, 0.01f);    
    }
};

/*
class SpriteShapeType : public ShapeType {
private:
    Sprite sprite_;  // Assumes there's a Sprite class defined somewhere
    
public:
    SpriteShapeType(const Sprite& sprite) : sprite_(sprite) {}

    void Draw() override {
        // Draw sprite using ImGui (or any other library)
    }
};*/

// Animated sprite can be another class or can be built into SpriteShapeType
