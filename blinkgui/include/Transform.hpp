#pragma once

#include "imgui.h"
#include <SDL.h>
#include <cmath>

struct Transform {
    ImVec2 position = {0,0};
    float rotation = 0; // Rotation in degrees
    ImVec2 scale = {1, 1};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    //Transform() : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {}
};

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