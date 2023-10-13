#include "Coordinate.hpp"

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
