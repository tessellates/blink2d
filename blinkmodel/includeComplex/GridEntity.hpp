#pragma once

#include <array>

using EntityType = int;
using Property = int;
using Properties = std::vector<int>;
using AdvancedProperties = std::array<double,8>;

template<typename Coordinate>
class GridEntity {
public:
    Coordinate position;
    EntityType type;
    Properties properties;
    AdvancedProperties advancedProperties;
    int gamestateId;

    GridEntity(const Coordinate& pos) : position(pos) {}

    std::vector<GridEntity*> links;
};
