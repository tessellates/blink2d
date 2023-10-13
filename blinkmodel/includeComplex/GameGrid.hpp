#pragma once

#include <Coordinate.hpp>
#include <GridEntity.hpp>

template<typename Coordinate>
class GameGrid {
    
    // This will remain empty or can contain common functionality
};

// Specialization for SquareCoordinate
template<>
class GameGrid<SquareCoordinate> {
public:
    int width, height;
    std::vector<std::vector<GridEntity<SquareCoordinate>*>> grid;

    GameGrid(int width, int height) : width(width), height(height), grid(width, std::vector<GridEntity<SquareCoordinate>*>(height)) {}

    // ... (other methods)
};

// Specialization for HexCoordinate
template<>
class GameGrid<HexCoordinate> {
public:
    HexOrientation orientation;

    int width, height;
    std::vector<std::vector<GridEntity<HexCoordinate>*>> layers[2]; // two layers

    GameGrid(int width, int height) : width(width), height(height) {
        layers[0] = std::vector<std::vector<GridEntity<HexCoordinate>*>>(width, std::vector<GridEntity<HexCoordinate>*>(height));
        layers[1] = std::vector<std::vector<GridEntity<HexCoordinate>*>>(width, std::vector<GridEntity<HexCoordinate>*>(height));
    }

    // You'll need to adjust the methods to account for the layer.
    // For example:
    void placeEntity(GridEntity<HexCoordinate>& entity, int a, int x, int y) {
        assert(a == 0 || a == 1); // Ensure a is 0 or 1
        layers[a][x][y] = &entity;
    }
};
    