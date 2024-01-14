#pragma once

#include "Coordinate.hpp"
#include "RockSolidLevel.hpp"
#include "CommandHistory.hpp"
#include "RockSolidNode.hpp"


// Forward declaration of classes used in the header
class RockSolidModel : public CommandHistory
{
public:
    RockSolidModel() = default;
    
    std::vector<RockSolidNode> nodeGrid;
    std::vector<std::function<void>(const Coordinate&, const RockSolidNodeType&)> replaceEmissions; 
    std::vector<std::function<void>(const Coordinate&, const Direction&)> directionEmissions; 
    std::vector<std::function<void>(const Coordinate&, const Coordinate&, int)> gemEmissions; 

    int height;
    int width;

    RockSolidNode& getNode(const Coordinate& position);
    const RockSolidNode& getNode(const Coordinate& position) const;
    bool inModel(const Coordinate& position) const;
    
    void placeNodeAtPosition(const Coordinate& position, RockSolidNodeType type);
    bool canPlaceNodeAtPosition(const Coordinate& position, RockSolidNodeType type) const;

    float demolitionCost(const Coordinate& position) const;
    float placeCost(const Coordinate& position, RockSolidNodeType type) const;
    float typeCost(RockSolidNodeType type) const;

    void nextTick();
    void loadLevel(const RockSolidLevel& level);

    float playerMoney;
    int gemTarget;
    int gemPerTick;

    std::unordered_map<RockSolidNodeType, float> nodeCosts = 
    {
        {RockSolidNodeType::HORIZONTAL_EXTRACTOR, 100.0f},
        {RockSolidNodeType::VERTICAL_EXTRACTOR, 100.0f},
        {RockSolidNodeType::HORIZONTAL_BELT, 100.0f},
        {RockSolidNodeType::VERTICAL_BELT, 100.0f},
        {RockSolidNodeType::HORIZONTAL_ENGINE, 100.0f},
        {RockSolidNodeType::VERTICAL_ENGINE, 100.0f},
        {RockSolidNodeType::CONSTRUCT_A, 100.0f},
        {RockSolidNodeType::CONSTRUCT_B, 100.0f},
        {RockSolidNodeType::CONSTRUCT_C, 100.0f}
    };
};
