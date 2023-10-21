#pragma once

#include <ShapeType.hpp>
#include <imgui.h>
#include <iostream>

class Shape {
public:
    std::shared_ptr<ShapeType> type_; 

    float animationFraction_;
    ImVec2 position_;
    ImVec2 sourcePosition_;

    Shape* uplayer_ = nullptr;

public:
    ~Shape()
    {
        clear();
    }
    Shape() = default;

    Shape(const std::shared_ptr<ShapeType>& type, const ImVec2& startPos)
        : type_(type), position_(startPos), sourcePosition_(startPos) {}

    void clear()
    {
        delete uplayer_;
        uplayer_ = nullptr; 
    }

    // Set the target position and calculate step values
    void moveFrom(float factor) {
        animationFraction_ = factor;
    }

    void startMovement(const ImVec2& sourcePosition)
    {
        sourcePosition_ = sourcePosition;
        animationFraction_ = 0.0;
    }

    void stopMovement()
    {
        sourcePosition_ = position_;
        animationFraction_ = 1.0;
    }

    void draw() {
        type_->draw(position_ + (sourcePosition_ - position_) * (1 - animationFraction_ ));
        if (uplayer_)
        {
            uplayer_->draw();
        }
    }

    void addLayer(const std::shared_ptr<ShapeType>& type)
    {
        clear();
        uplayer_ = new Shape(type, position_);
    }

    void reset()
    {
        clear();
        stopMovement();
        type_ = ColorShapeTypeFactory::getColorShape(ImVec4(0, 0, 0, 0), type_->size_);
    }
};