#pragma once
#include <GridEntity.hpp>

class GameGrid {
public:
    int width, height;
    std::vector<std::vector<GridEntity*>> grid;
    GridEntity* activeEntity;
    GameGrid(int width, int height) : width(width), height(height), grid(width, std::vector<GridEntity*>(height, nullptr)) {}
};