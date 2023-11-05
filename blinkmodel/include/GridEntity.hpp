#pragma once

#include <array>
#include <Coordinate.hpp>

using EntityType = int;
using Property = int;
using Properties = std::vector<Property>;

class GridEntity {
public:
    Coordinate position;
    EntityType type;
    Properties properties;
    GridEntity(const Coordinate& pos, EntityType type = 0) : position(pos), type(type) {}
};

