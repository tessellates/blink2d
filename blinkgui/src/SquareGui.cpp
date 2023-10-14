#include <iostream>
#include <SquareGui.hpp>
#include <Application.hpp>

namespace blink2dgui
{
    SquareGui::SquareGui()
    {
        nPixels_ = 1280.0f;
        squareSize_ = 30.0f;
        window_flags_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        windowPos_ = ImVec2((1280- nPixels_) * 0.5, (1280 - nPixels_) * 0.5);

        int gridWidth = nPixels_ / squareSize_ -1;
        int gridHeight = nPixels_ / squareSize_ -1;


        shapes_ = std::vector<Shape>(gridWidth*gridHeight);
        ShapeType* type = new ColorShapeType(ImVec4(0,0,0,1));
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

    void SquareGui::interpretEntity(const GridEntity& entity)
    {
        ImVec4 color;
        if (entity.type == 0)
        {
            color = ImVec4(0.5f, 0.5f, 0, 1);
        }
        else
        {
            color = ImVec4(0.5f, 0, 0, 1);
        }
    }

}
