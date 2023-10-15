#include <iostream>
#include <SquareGui.hpp>
#include <Application.hpp>

namespace blink2dgui
{
    SquareGui::SquareGui(float squareSize)
    {
        nPixels_ = 720.0f;
        squareSize_ = squareSize;
        window_flags_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        windowPos_ = ImVec2((1280- nPixels_) * 0.5, (800 - nPixels_) * 0.5);

        int gridWidth = nPixels_ / squareSize_ -1;
        int gridHeight = nPixels_ / squareSize_ -1;


        shapes_ = std::vector<Shape>(gridWidth*gridHeight);
        ShapeType* type = new ColorShapeType(ImVec4(0,0,0,0));
        // Centering adjustments
        float startX = squareSize_;
        float startY = squareSize_;
        for (int y = 0; y < gridHeight; ++y) 
        {
            for (int x = 0; x < gridWidth; ++x) 
            {
                float xPos = startX + x * squareSize_;
                float yPos = startY + y * squareSize_;

                shapes_[x*gridHeight + y] = Shape(type->clone(), ImVec2(windowPos_.x + xPos, windowPos_.y + yPos));
            }
        }
    }

    SquareGui::~SquareGui()
    {
    }

    void SquareGui::renderGrid()
    {
        ImVec2 windowSize = ImVec2(nPixels_, nPixels_);  // Example size
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos_);

        ImGui::Begin("Square Grid", nullptr, window_flags_);

        ImVec2 mousePos = ImGui::GetMousePos();
        
        for (size_t i = 0; i < shapes_.size(); ++i) 
        {
            // Translate the local square center to global screen position
            shapes_[i].draw();
            
        }
        
        ImGui::End();
    }

    void SquareGui::colorLocation(const Coordinate& pos, const ImVec4& color)
    {
        int gridHeight = nPixels_ / squareSize_ -1;
        auto& targetShape = shapes_[pos.x*gridHeight + pos.y];
        targetShape.type_.reset(new ColorShapeType(color));
        targetShape.sourcePosition_ = targetShape.position_;
    }

    void SquareGui::moveColorLocation(const Coordinate& previousPosition, const Coordinate& pos, const ImVec4& color)
    {
        int gridHeight = nPixels_ / squareSize_ -1;
        ImVec2 imPreviousPosition = shapes_[previousPosition.x*gridHeight + previousPosition.y].position_;
        auto& targetShape = shapes_[pos.x*gridHeight + pos.y];
        targetShape.type_.reset(new ColorShapeType(color));
        targetShape.sourcePosition_ = imPreviousPosition;
    }

    void SquareGui::updateShapeMovement(const Coordinate& pos, float factor)
    {
        int gridHeight = nPixels_ / squareSize_ -1;
        shapes_[pos.x*gridHeight + pos.y].moveFrom(factor);
    }
}
