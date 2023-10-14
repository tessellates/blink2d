#pragma once

#include <ShapeType.hpp>

class Shape {
private:
    std::unique_ptr<ShapeType> type_;
    ImVec2 position_;
    ImVec2 targetPosition_;
    ImVec2 step_;  // Amount to move each frame towards target position
    int stepsRemaining_;

public:
    Shape() = default;

    Shape(std::unique_ptr<ShapeType> type, const ImVec2& startPos)
        : type_(std::move(type)), position_(startPos), stepsRemaining_(0) {}

    Shape(const Shape& other) {
        if (other.type_) {
            type_ = other.type_->clone();
        }
        position_ = (other.position_);
        targetPosition_ =(other.targetPosition_);
        step_ = (other.step_);
        stepsRemaining_ = (other.stepsRemaining_);
    }
    
    // Copy assignment operator
    Shape& operator=(const Shape& other) {
        if (&other == this) return *this;  // self-assignment check

        if (other.type_) {
            type_ = other.type_->clone();
        } else {
            type_.reset();
        }

        position_ = (other.position_);
        targetPosition_ = (other.targetPosition_);
        step_ = (other.step_);
        stepsRemaining_ = (other.stepsRemaining_);

        return *this;
    }

    // Set the target position and calculate step values
    void moveTo(const ImVec2& target, int totalSteps) {
        targetPosition_ = target;
        stepsRemaining_ = totalSteps;
        
        // Calculate step values based on total steps and distance to cover
        step_.x = (targetPosition_.x - position_.x) / totalSteps;
        step_.y = (targetPosition_.y - position_.y) / totalSteps;
    }

    void update() {
        // Move the Shape towards the target by one step if steps remain
        if(stepsRemaining_ > 0) {
            position_.x += step_.x;
            position_.y += step_.y;
            --stepsRemaining_;
            
            // If we've reached or overshot the target (due to floating point inaccuracies), fix the position
            if((step_.x > 0 && position_.x > targetPosition_.x) || (step_.x < 0 && position_.x < targetPosition_.x)) {
                position_.x = targetPosition_.x;
            }
            if((step_.y > 0 && position_.y > targetPosition_.y) || (step_.y < 0 && position_.y < targetPosition_.y)) {
                position_.y = targetPosition_.y;
            }
        }
    }

    void draw() {
        type_->draw(position_);
    }
};