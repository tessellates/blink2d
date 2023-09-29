#include <iostream>
#include <HexGui.hpp>
#include <cmath>

namespace blink2dgui
{
    HexGui::HexGui()
    {
        nPixels_ = 720.0f;
        hexRadius_ = 30.0f;
        window_flags_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        windowPos_ = ImVec2((1280- nPixels_) * 0.5, (800 - nPixels_) * 0.5);

        float hexHeight = sqrt(3) * hexRadius_;
        float hexWidth = 2.0f * hexRadius_;

        int gridWidth = nPixels_/hexHeight+1;
        int gridHeight = nPixels_/hexHeight;

        float vertDist = hexHeight;
        float horzDist = 1.5f * hexRadius_;

        float totalGridWidth = (gridWidth * hexWidth + (gridWidth - 1) * (hexWidth - hexRadius_));
        float totalGridHeight = (gridHeight * hexHeight);

        hexCenters_ = std::vector<ImVec2>(gridWidth*gridHeight);

        // Centering adjustments
        float startX = hexWidth+0*(nPixels_-totalGridWidth) * 0.5f;
        float startY = (nPixels_-totalGridHeight) * 0.5f;
        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                float xPos = startX + x * horzDist;
                float yPos = startY + y * vertDist;

                // Offset every other row
                if (x % 2 == 1) {
                    yPos += hexHeight * 0.5f;
                }

                hexCenters_[x*gridHeight + y] = ImVec2(xPos, yPos);
            }
        }
        

        hexColors_ = std::vector<ImVec4>(hexCenters_.size(), ImVec4(0,0,0,1)); 
    }

    HexGui::~HexGui()
    {
    }

    void HexGui::drawHexagon(const ImVec2& center, float radius, const ImVec4& color) 
    {
        const int numSegments = 6;  // A hexagon has 6 sides

        ImVec2 vertices[numSegments];

        const float PI = 3.14159265358979323846f;

        // Calculate the vertices of the hexagon based on its center and radius
        for (int i = 0; i < numSegments; ++i) 
        {
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);  // Angle for each segment
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            vertices[i] = ImVec2(center.x + dx, center.y - dy);  // Note: y is subtracted because of inverted Y-axis in some graphics systems
        }

        // Draw the hexagon using ImGui's polygon drawing function
        // Convert the ImVec4 color to a ImU32
        ImU32 imColor = IM_COL32((int)(color.x * 255.0f), (int)(color.y * 255.0f), (int)(color.z * 255.0f), (int)(color.w * 255.0f));

        // Fetch draw list
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Draw filled polygon
        drawList->AddConvexPolyFilled(vertices, numSegments, imColor);

        // Calculate the vertices of the hexagon based on its center and radius
        for (int i = 0; i < numSegments; ++i) 
        {
            float angle1 = (2.0f * PI / 6) * (i + 0);
            float angle2 = (2.0f * PI / 6) * (i + 1);

            ImGui::GetWindowDrawList()->AddLine(
                ImVec2(center.x + radius * cos(angle1), center.y + radius * sin(angle1)),
                ImVec2(center.x + radius * cos(angle2), center.y + radius * sin(angle2)),
                IM_COL32(255, 255, 255, 255)
            );
        }
    }


    void HexGui::renderGrid()
    {
        ImVec2 windowSize = ImVec2(nPixels_, nPixels_);  // Example size
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos_);

        ImGui::Begin("Hexagonal Grid", nullptr, window_flags_);
        ImVec2 mousePos = ImGui::GetMousePos();

        for (size_t i = 0; i < hexCenters_.size(); ++i) 
        {
            // Translate the local hex center to global screen position
            ImVec2 globalHexCenter = ImVec2(windowPos_.x + hexCenters_[i].x, windowPos_.y +10 + hexCenters_[i].y);
            
            // Draw the hexagon with its respective color
            drawHexagon(globalHexCenter, hexRadius_, hexColors_[i]);

            // Check if this hexagon was clicked
            if (ImGui::IsMouseClicked(0))
            {
                float distanceToHexCenter = std::sqrt((mousePos.x - globalHexCenter.x) * (mousePos.x - globalHexCenter.x) + 
                                                    (mousePos.y - globalHexCenter.y) * (mousePos.y - globalHexCenter.y));
                if (distanceToHexCenter < hexRadius_-5)
                {
                    // Toggle color between black and yellow
                    if (hexColors_[i].x == 0)
                        hexColors_[i] = ImVec4(0.5f,0.5f,0,1); // Yellow
                    else
                        hexColors_[i] = ImVec4(0,0.1f,0.1f,1); // Black
                }
            }
        }
        
        ImGui::End();
    }

}