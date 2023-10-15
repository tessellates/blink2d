#pragma once

#include <ShapeType.hpp>
#include <imgui.h>

class Shape {
public:
    std::unique_ptr<ShapeType> type_;
    ImVec2 position_;
    ImVec2 sourcePosition_;
    ImVec2 step_;

public:
    Shape() = default;

    Shape(std::unique_ptr<ShapeType> type, const ImVec2& startPos)
        : type_(std::move(type)), position_(startPos), sourcePosition_(startPos), step_(ImVec2(0,0)) {}

    Shape(const Shape& other) {
        if (other.type_) {
            type_.reset();
            type_ = other.type_->clone();
        }
        position_ = (other.position_);
        sourcePosition_ = (other.sourcePosition_);
        step_ = (other.step_);
    }
    
    // Copy assignment operator
    Shape& operator=(const Shape& other) {
        if (&other == this) return *this;  // self-assignment check

        if (other.type_) {
            type_.reset();
            type_ = other.type_->clone();
        } else {
            type_.reset();
        }
        position_ = (other.position_);
        sourcePosition_ = (other.sourcePosition_);
        step_ = (other.step_);
        return *this;
    }

    // Set the target position and calculate step values
    void moveFrom(float factor) {
        // Calculate step values based on total steps and distance to cover
        step_.x = (sourcePosition_.x - position_.x) / factor;
        step_.y = (sourcePosition_.y - position_.y) / factor;
    }


    void draw() {
        ImVec2 vec = sourcePosition_ + step_;        
        type_->draw(vec);
    }
};