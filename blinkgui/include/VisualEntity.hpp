#pragma once

#include "Transform.hpp"
#include "TransformStrategy.hpp"
#include "RenderInstruction.hpp"

class VisualEntity {
public:
    VisualEntity() = default;
    ~VisualEntity() = default;

    VisualEntity(const VisualEntity&) = delete;
    VisualEntity& operator=(const VisualEntity&) = delete;

    VisualEntity(VisualEntity&&) = default;
    VisualEntity& operator=(VisualEntity&&) = default;

    //const Transform& getAbsoluteTransform();
    void render();

    void clean();

    std::optional<MoveStrategy> ms;
    std::vector<RenderInstruction> renderInstructions;

public:
    //VisualEntity* parent;
    //std::vector<VisualEntity*> children;
    
    Transform transform;
};