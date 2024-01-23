#pragma once

#include "imgui.h"
#include <SDL.h>
#include <cmath>

struct Transform {
    ImVec2 position = {0,0};
    double rotation = 0; // Rotation in degrees
    ImVec2 scale = {1, 1};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //Transform() : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {}
};

inline ImVec2 rotateVector(const ImVec2& v, double angleDegrees) {
    float angleRadians = angleDegrees * M_PI / 180.0f;
    float cosAngle = std::cos(angleRadians);
    float sinAngle = std::sin(angleRadians);

    return ImVec2(v.x * cosAngle - v.y * sinAngle, v.x * sinAngle + v.y * cosAngle);
}


inline Transform relativeAddition(const Transform& first, const Transform& second) {
    ImVec2 rotatedPosition = rotateVector(second.position, first.rotation);
    return Transform{
        ImVec2(first.position.x + rotatedPosition.x, first.position.y + rotatedPosition.y),
        0, // Assuming rotation and scale are not cumulative
        ImVec2(1, 1), // Same here for the scale
        SDL_FLIP_NONE // And for flip
    };
}

// Operator + for Transform
inline Transform operator+(const Transform& a, const Transform& b) {
    Transform result;
    result.position = a.position + b.position; // Assuming ImVec2 supports operator+
    result.rotation = a.rotation + b.rotation;
    result.scale = a.scale; // Scale and flip are not affected
    result.flip = a.flip;
    return result;
}

// Operator - for Transform
inline Transform operator-(const Transform& a, const Transform& b) {
    Transform result;
    result.position = a.position - b.position; // Assuming ImVec2 supports operator-
    result.rotation = a.rotation - b.rotation;
    result.scale = a.scale; // Scale and flip are not affected
    result.flip = a.flip;
    return result;
}

inline ImVec2 lerp(const ImVec2& a, const ImVec2& b, float t) {
    return {
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
}

inline ImVec2 lerpVec(const ImVec2& a, const ImVec2& b, float t) {
    return {
        (b.x - a.x) * t,
        (b.y - a.y) * t
    };
}

bool moveTowards(ImVec2& source, const ImVec2& target, float speed);
ImVec2 moveVec(const ImVec2& source, const ImVec2& target, float speed);