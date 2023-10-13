#pragma once

#include <Direction.hpp>
#include <CRTP.hpp>
#include <vector>
#include <iostream>

enum HexOrientation {
    POINTY_TOPPED,
    FLAT_TOPPED
};

enum SquareOrientation {
    NORMAL,
    DIAGONAL
};

template<typename _DerivedSpace>
class CoordinateBase : public CRTP<_DerivedSpace>  {
public:
    using DerivedSpace = _DerivedSpace;

    void print() const {
        this->derived().printImpl();
    }

    DerivedSpace getNeighbor(int direction) const {
        // Uses the Derived class's getNeighborImpl method
        return this->derived().getNeighbor(direction);
    }
};

class SquareCoordinate : public CoordinateBase<SquareCoordinate> 
{
    int x, y;

public:
    SquareCoordinate(int x, int y) : x(x), y(y) {}

    // Implementation for square coordinates
    void printImpl() const {
        std::cout << "Square Coordinate: (" << x << ", " << y << ")\n";
    }

    SquareCoordinate getNeighbor(const SquareCoordinate& sq, int direction) const
    {
        static std::array<std::pair<int, int>, 8> directions = {
            std::make_pair(0, -1),    // UP
            std::make_pair(1, -1),    // UP_RIGHT
            std::make_pair(1, 0),     // RIGHT
            std::make_pair(1, 1),     // DOWN_RIGHT
            std::make_pair(0, 1),     // DOWN
            std::make_pair(-1, 1),    // DOWN_LEFT
            std::make_pair(-1, 0),    // LEFT
            std::make_pair(-1, -1)    // UP_LEFT
        };

        int dx = directions[direction].first;
        int dy = directions[direction].second;

        return SquareCoordinate(x + dx, y + dy);
    }
};

class HexCoordinate : public CoordinateBase<HexCoordinate> {
private:
    int a; // Altitude
    int r; // Row
    int c; // Column
    HexOrientation orientation = POINTY_TOPPED;

public:
    HexCoordinate(int a, int r, int c, HexOrientation orientation) : a(a), r(r), c(c), orientation(orientation) {}
    HexCoordinate(int a, int r, int c) : a(a), r(r), c(c) {}
    // Implementation for hexagonal coordinates
    void printImpl() const {
        std::cout << "Hex Coordinate: (a=" << a << ", r=" << r << ", c=" << c << ")\n";
    }

    HexCoordinate getNeighborImpl(const HexCoordinate& hex, int direction) const
    {
    // Define direction as an int from 0 to 5 (six possible neighbors for a hexagon)

        static std::pair<int, int> pointy_directions[6] = {
            {-1, 0}, {0, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 1}
        };

        static std::pair<int, int> flat_directions[6] = {
            {-1, -1}, {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}
        };

        int dx, dy;
        if (hex.orientation == HexOrientation::POINTY_TOPPED) {
            dx = pointy_directions[direction].first;
            dy = pointy_directions[direction].second;
        } else {
            dx = flat_directions[direction].first;
            dy = flat_directions[direction].second;
        }

        return HexCoordinate(hex.a, hex.r + dx, hex.c + dy, hex.orientation);
    }
};