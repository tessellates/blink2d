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

    void render();

    std::optional<MoveStrategy> ms;
    std::vector<RenderInstruction> renderInstructions;
public:
    //std::map<std::string, std::unique_ptr<IRenderStrategy>> renderStrategies;
    //std::map<std::string, std::unique_ptr<ITransformStrategy>> transformStrategies;

    Transform transform;
};