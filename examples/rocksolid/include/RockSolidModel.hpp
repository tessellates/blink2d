#pragma once

#include "Coordinate.hpp"
#include "GameState.hpp"
#include "RockSolidLevel.hpp"
#include "RockSolidNode.hpp"


enum RockSolidModelNodeProperties
{
    GEM_COUNT
};

// Forward declaration of classes used in the header
class RockSolidModel : public GameState
{
public:
    RockSolidModel() = default;
    
    std::vector<std::vector<RockSolidNode>> nodeGrid;

    RockSolidNode& getNode(const Coordinate& position);
    const RockSolidNode& getNode(const Coordinate& position) const;

    bool inModel(const Coordinate& position) const;
    
    int height() const;
    int width() const;

    void placeNodeAtPosition(const Coordinate& position, RockSolidNodeType type);
    bool canPlaceNodeAtPosition(const Coordinate& position, RockSolidNodeType type) const;

    float demolitionCost(const Coordinate& position) const;
    float placeCost(const Coordinate& position, RockSolidNodeType type) const;
    float typeCost(RockSolidNodeType type) const;

    void nextTick();
    void loadLevel(const RockSolidLevel& level);


    void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireAddEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireReplaceEntity(const Coordinate&, const GridEntity&, const GridEntity&) override;

    float playerMoney;
    int gemTarget;

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

    /*
    void play(int column);
    void fireRemoveEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireAddEntity(const Coordinate& cor, const GridEntity& ent) override;
    void fireWin();
    std::optional<std::vector<Coordinate>> checkWin(const std::vector<std::stack<int>>& board, int player);

public:
    std::vector<std::stack<int>> board;
    std::optional<std::vector<Coordinate>> win;*/
};
