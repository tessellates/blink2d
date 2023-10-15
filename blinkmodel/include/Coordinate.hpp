#pragma once
#include <iostream>

class Coordinate {
public:
    int x;
    int y;

    // Default constructor
    Coordinate();

    // Parameterized constructor
    Coordinate(int x_, int y_);

    // Equality operator
    bool operator==(const Coordinate& other) const;

    // Inequality operator
    bool operator!=(const Coordinate& other) const;

    // Addition operator
    Coordinate operator+(const Coordinate& other) const;

    // Subtraction operator
    Coordinate operator-(const Coordinate& other) const;

    Coordinate getNeighbor(int direction) const;

    // Print the coordinate (for debugging)
    void print() const;
};
