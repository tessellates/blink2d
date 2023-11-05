#pragma once

#include "imgui.h"
#include <random>
#include <iostream>

#include <map>
#include <tuple>

class ShapeType {
public:
    float size_ = 30;
    ShapeType(float size) : size_(size) {};
    ShapeType() = default;
    virtual void draw(const ImVec2& center) = 0;
    virtual ~ShapeType() = default;
};

class ColorShapeType : public ShapeType {
private:
    ImVec4 color_;
    
public:
    ColorShapeType(const ImVec4& color, float size) : ShapeType(size), color_(color){}
    void draw(const ImVec2& center) override;
};

/*
class SpriteShapeType : public ShapeType {
private:
    Sprite sprite_;  // Assumes there's a Sprite class defined somewhere
    
public:
    SpriteShapeType(const Sprite& sprite) : sprite_(sprite) {}

    void Draw() override {
        // Draw sprite using ImGui (or any other library)
    }
};*/

// Animated sprite can be another class or can be built into SpriteShapeType


struct CompareTuple {
    bool operator()(const std::tuple<ImVec4, float>& a, const std::tuple<ImVec4, float>& b) const {
        // Here we are comparing the tuples first based on the ImVec4 and then on the float.
        // Adjust the logic if you have a different criterion for "less than".

        const auto& [colorA, sizeA] = a;
        const auto& [colorB, sizeB] = b;

        // Compare the ImVec4 first (you may want to consider epsilon comparison for floating-point values)
        if (colorA.x < colorB.x) return true;
        if (colorA.x > colorB.x) return false;
        if (colorA.y < colorB.y) return true;
        if (colorA.y > colorB.y) return false;
        if (colorA.z < colorB.z) return true;
        if (colorA.z > colorB.z) return false;
        if (colorA.w < colorB.w) return true;
        if (colorA.w > colorB.w) return false;
        // ... Similarly for y, z, and w components

        // If ImVec4 components are equal, compare the float size
        return sizeA < sizeB;
    }
};

class ColorShapeTypeFactory {
private:
    static std::map<std::tuple<ImVec4, float>, std::shared_ptr<ColorShapeType>, CompareTuple> colorShapeCache;

public:
    ColorShapeTypeFactory() = delete;
    static std::shared_ptr<ColorShapeType> getColorShape(const ImVec4& color, float size) {
        // Create a tuple based on color and size
        auto key = std::make_tuple(color, size);

        // Try to find the color shape in the cache
        auto it = colorShapeCache.find(key);
        if (it != colorShapeCache.end()) {
            return it->second; // If found, return the existing instance
        }

        // If not found, create a new instance and save it in the cache
        std::shared_ptr<ColorShapeType> newColorShape = std::make_shared<ColorShapeType>(color, size);
        newColorShape->size_ = size; // Assume the size can be set publicly or through a method.
        colorShapeCache[key] = newColorShape;

        return newColorShape;
    }
};
