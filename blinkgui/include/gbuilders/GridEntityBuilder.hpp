#pragma once

#include "VisualEntity.hpp"
#include "Coordinate.hpp"

class GridEntityBuilder {
public:
    // Constructor to initialize grid size or scale
    GridEntityBuilder(int nx, int ny, const ImVec2& gridSize, const ImVec2& gridLocation);
    GridEntityBuilder() = default;
    ~GridEntityBuilder() = default;

    GridEntityBuilder(const GridEntityBuilder&) = delete;
    GridEntityBuilder& operator=(const GridEntityBuilder&) = delete;

    GridEntityBuilder(GridEntityBuilder&&) = default;
    GridEntityBuilder& operator=(GridEntityBuilder&&) = default;

    GridEntityBuilder& atLocation(const Coordinate& Coordinate);
    GridEntityBuilder& instructionLayer(int layer);
    GridEntityBuilder& instructionLocation(const Coordinate& Coordinate);
    GridEntityBuilder& instructionTexture(const BlinkTexture& texture);
    GridEntityBuilder& instructionMoveStrategy(float gameTicks, const Coordinate& Coordinate = {0,0}); 

    VisualEntity build();
    GridEntityBuilder& addInstruction(); 

    ImVec2 absolutePosition(const Coordinate& pos) const;
    ImVec2 relativePosition(const Coordinate& pos) const;

public:
    int nx;
    int ny;

    std::unique_ptr<VisualEntity> entity;
    std::unique_ptr<RenderInstruction> instruction;

    ImVec2 gridLocation;
    ImVec2 entitySize;
    ImVec2 gridSize;
};

VisualEntity entryAnimatedEntity(GridEntityBuilder& builder, const Coordinate& pos, const Coordinate& relativeEntry, const BlinkTexture& texture, float gameTicks, int layer);
VisualEntity quadEntryAnimatedEntity(GridEntityBuilder& builder, const Coordinate& pos, int relativeEntry, const BlinkTexture& texture, float gameTicks, int layer);
VisualEntity staticEntity(GridEntityBuilder& builder, const Coordinate& pos, const BlinkTexture& texture, int layer);