#include "Coordinate.hpp"
#include <array>


// Default constructor
Coordinate::Coordinate() : x(0), y(0) {}

// Parameterized constructor
Coordinate::Coordinate(int x_, int y_) : x(x_), y(y_) {}

// Equality operator
bool Coordinate::operator==(const Coordinate& other) const {
    return x == other.x && y == other.y;
}

// Inequality operator
bool Coordinate::operator!=(const Coordinate& other) const {
    return !(*this == other);
}

// Addition operator
Coordinate Coordinate::operator+(const Coordinate& other) const {
    return Coordinate(x + other.x, y + other.y);
}

// Subtraction operator
Coordinate Coordinate::operator-(const Coordinate& other) const {
    return Coordinate(x - other.x, y - other.y);
}

// Print the coordinate (for debugging)
void Coordinate::print() const {
    std::cout << "Coordinate(" << x << ", " << y << ")\n";
}


Coordinate Coordinate::getNeighbor(int direction) const
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

    return Coordinate(x + dx, y + dy);
}

Direction Coordinate::getDirection(const Coordinate& other) const {
    int dx = other.x - x;
    int dy = other.y - y;

    // Normalize dx and dy to -1, 0, or 1
    dx = (dx != 0) ? (dx / abs(dx)) : 0;
    dy = (dy != 0) ? (dy / abs(dy)) : 0;

    if (dx == 0 && dy == -1) return UP;
    else if (dx == 1 && dy == -1) return UP_RIGHT;
    else if (dx == 1 && dy == 0) return RIGHT;
    else if (dx == 1 && dy == 1) return DOWN_RIGHT;
    else if (dx == 0 && dy == 1) return DOWN;
    else if (dx == -1 && dy == 1) return DOWN_LEFT;
    else if (dx == -1 && dy == 0) return LEFT;
    else if (dx == -1 && dy == -1) return UP_LEFT;
    else return NONE; // Indicates no direction (same coordinate or not a direct neighbor)
}