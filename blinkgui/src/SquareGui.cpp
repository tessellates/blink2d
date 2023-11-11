#include <iostream>
#include "SquareGui.hpp"
#include "Application.hpp"
#include "ShapeType.hpp"
#include "BackgroundTexture.hpp"

namespace blink2dgui
{
    SquareGui::SquareGui(int gridSize)
    {
        squareSize_ = (float) nPixels_ / (gridSize + 1);
        window_flags_ = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        windowPos_ = ImVec2((1280 - nPixels_) * 0.5, (800 - nPixels_) * 0.5);

        gridWidth_ = gridSize;
        gridHeight_ = gridSize;


        shapes_ = std::vector<Shape>(gridWidth_*gridHeight_);
        // Centering adjustments
        float startX = squareSize_;
        float startY = squareSize_;
        texture_id = CreateBackgroundTexture(Application::instance()->getRenderer(), squareSize_,  nPixels_, nPixels_);

        for (int y = 0; y < gridHeight_; ++y) 
        {
            for (int x = 0; x < gridWidth_; ++x) 
            {
                float xPos = startX + x * squareSize_;
                float yPos = startY + y * squareSize_;

                shapes_[x*gridHeight_ + y] = Shape(ColorShapeTypeFactory::getColorShape(ImVec4(0,0,0,0), squareSize_), ImVec2(windowPos_.x + xPos, windowPos_.y + yPos));
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

        ImGuiStyle originalStyle = ImGui::GetStyle();

        // Modify the style for a specific window
        ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

        ImGui::Begin("Square Grid", nullptr, window_flags_);
        ImGui::Image(texture_id, windowSize);

        for (size_t i = 0; i < shapes_.size(); ++i) 
        {
            // Translate the local square center to global screen position
            shapes_[i].draw();
            
        }

        ImGui::End();
        ImGui::GetStyle() = originalStyle;
    }

    void SquareGui::colorLocation(const Coordinate& pos, const ImVec4& color, bool addLayer)
    {
        auto& targetShape = getShape(pos);
        if (addLayer)
        {
            targetShape.addLayer(ColorShapeTypeFactory::getColorShape(color, squareSize_));
            return;
        }
        targetShape.type_ = ColorShapeTypeFactory::getColorShape(color, squareSize_);
    }

    void SquareGui::clearPos(const Coordinate& pos)
    {
        getShape(pos).reset();
    }
    void SquareGui::moveAnimate(const Coordinate& previousPosition, const Coordinate& pos)
    {
        const auto& imPreviousPosition = getShape(previousPosition).position_;
        auto& targetShape = getShape(pos);
        targetShape.startMovement(imPreviousPosition);
    }

    void SquareGui::stopMovement(const Coordinate& pos)
    {
        getShape(pos).stopMovement();
    }

    void SquareGui::updateShapeMovement(const Coordinate& pos, float factor)
    {
        getShape(pos).moveFrom(factor);
        if (factor >= 1)
        {
            stopMovement(pos);
        }
    }

    Shape& SquareGui::getShape(const Coordinate& pos)
    {
        return shapes_[pos.x*gridHeight_ + pos.y];
    }
}
