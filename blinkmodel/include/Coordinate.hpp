#pragma once
#include <iostream>
#include <functional> 
#include "Direction.hpp"

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
    Direction getDirection(const Coordinate&) const;

    // Print the coordinate (for debugging)
    void print() const;
};

/*
Specialize std::hash for the Coordinate class. A common approach is to combine the hashes of individual members (in this case, x and y) using a bitwise XOR (^) operation, often combined with a bitwise left shift (<<). This helps in generating a unique hash value for each unique combination of x and y.
*/
template <>
struct std::hash<Coordinate> 
{
    std::size_t operator()(const Coordinate& coord) const {
        // Combine the hash of the individual members using XOR and bit shifting
        return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
    }
};
