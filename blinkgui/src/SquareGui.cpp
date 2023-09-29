#include <iostream>
#include <SquareGui.hpp>

namespace blink2dgui
{
    SquareGui::SquareGui()
    {
        nPixels_ = 720.0f;
        squareSize_ = 30.0f;
        window_flags_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        windowPos_ = ImVec2((1280- nPixels_) * 0.5, (800 - nPixels_) * 0.5);

        int gridWidth = nPixels_ / squareSize_ -1;
        int gridHeight = nPixels_ / squareSize_ -1;

        squareCenters_ = std::vector<ImVec2>(gridWidth*gridHeight);

        // Centering adjustments
        float startX = squareSize_;
        float startY = squareSize_;
        for (int y = 0; y < gridHeight; ++y) 
        {
            for (int x = 0; x < gridWidth; ++x) 
            {
                float xPos = startX + x * squareSize_;
                float yPos = startY + y * squareSize_;

                squareCenters_[x*gridHeight + y] = ImVec2(xPos, yPos);
            }
        }

        squareColors_ = std::vector<ImVec4>(squareCenters_.size(), ImVec4(0,0,0,1)); 
    }

    SquareGui::~SquareGui()
    {
    }

    void SquareGui::drawSquare(const ImVec2& center, float size, const ImVec4& color) 
    {
        ImVec2 topLeft = ImVec2(center.x - size/2, center.y - size/2);
        ImVec2 bottomRight = ImVec2(center.x + size/2, center.y + size/2);
        
        ImU32 imColor = IM_COL32((int)(color.x * 255.0f), (int)(color.y * 255.0f), (int)(color.z * 255.0f), (int)(color.w * 255.0f));
        
        // Fetch draw list
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Draw filled square
        drawList->AddRectFilled(topLeft, bottomRight, imColor);

         // Draw border (gridline) for the square
        ImU32 borderColor = IM_COL32(50, 50, 50, 255);  // White color for the border
        drawList->AddRect(topLeft, ImVec2(topLeft.x + size, topLeft.y + size), borderColor, 0.0f, ImDrawFlags_None, 0.01f);
    }

    void SquareGui::renderGrid()
    {
        ImVec2 windowSize = ImVec2(nPixels_, nPixels_);  // Example size
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos_);

        ImGui::Begin("Square Grid", nullptr, window_flags_);

        ImVec2 mousePos = ImGui::GetMousePos();
        
        for (size_t i = 0; i < squareCenters_.size(); ++i) 
        {
            // Translate the local square center to global screen position
            ImVec2 globalSquareCenter = ImVec2(windowPos_.x + squareCenters_[i].x, windowPos_.y + squareCenters_[i].y);
                
            // Draw the square with its respective color
            //float diagonalSize = std::sqrt(2) * squareSize_;
            drawSquare(globalSquareCenter, squareSize_, squareColors_[i]);

            // Check if this square was clicked
            if (ImGui::IsMouseClicked(0))
            {
                bool withinXBounds = mousePos.x > globalSquareCenter.x - squareSize_/2 && mousePos.x < globalSquareCenter.x + squareSize_/2;
                bool withinYBounds = mousePos.y > globalSquareCenter.y - squareSize_/2 && mousePos.y < globalSquareCenter.y + squareSize_/2;

                if (withinXBounds && withinYBounds)
                {
                    // Toggle color between black and yellow
                    if (squareColors_[i].x == 0)
                        squareColors_[i] = ImVec4(0.5f, 0.5f, 0, 1); // Yellow
                    else
                        squareColors_[i] = ImVec4(0, 0, 0, 1); // Black
                }
            }
        }
        
        ImGui::End();
    }

}
