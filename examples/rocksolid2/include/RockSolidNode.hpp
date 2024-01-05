#pragma once

#include "Coordinate.hpp"
#include "GridEntity.hpp"

enum DemolitionThreshold
{
    SOFT,
    HARD,
    INDESTRUCTABLE
};

enum RockSolidNodeType {
    EMPTY = 1 << 0,              // 1
    DIRT = 1 << 1,               // 2
    ROCK = 1 << 2,               // 4
    GEM_DEPOSIT = 1 << 3,        // 8
    EXIT = 1 << 4,               // 16
    HORIZONTAL_EXTRACTOR = 1 << 5,   // 32
    VERTICAL_EXTRACTOR = 1 << 6,     // 64
    HORIZONTAL_BELT = 1 << 7,        // 128
    VERTICAL_BELT = 1 << 8,          // 256
    HORIZONTAL_ENGINE = 1 << 9,      // 512
    VERTICAL_ENGINE = 1 << 10,       // 1024
    CONSTRUCT_A = 1 << 11,           // 2048
    CONSTRUCT_B = 1 << 12,           // 4096
    CONSTRUCT_C = 1 << 13,           // 8192
    BEDROCK = 1 << 14               // 16384
};

// Forward declaration of classes used in the header
class RockSolidNode 
{
public:
    RockSolidNode() = default;
    RockSolidNode(RockSolidNodeType type, int gemCount = 0);
    RockSolidNode(const GridEntity& entity);

    void change(RockSolidNodeType type);

    GridEntity entity(const Coordinate& position) const;

    void onGameTick();
    std::function<void(RockSolidNode&)>* gameTickBehaviour;
    
    DemolitionThreshold demolitionThreshold = INDESTRUCTABLE;
    RockSolidNodeType type = EMPTY;
    int gemCount = 0;
    int canPlace = 0;

    // STATIC
    static std::unordered_map<RockSolidNodeType, std::function<void(RockSolidNode&)>> initMap;
    static void initializeEmpty(RockSolidNode& node);
    static void initializeDirt(RockSolidNode& node);
    static void initializeRock(RockSolidNode& node);
    static void initializeGemDeposit(RockSolidNode& node);
    static void initializeExit(RockSolidNode& node);
    static void initializeHorizontalExtractor(RockSolidNode& node);
    static void initializeVerticalExtractor(RockSolidNode& node);
    static void initializeHorizontalBelt(RockSolidNode& node);
    static void initializeVerticalBelt(RockSolidNode& node);
    static void initializeHorizontalEngine(RockSolidNode& node);
    static void initializeVerticalEngine(RockSolidNode& node);
    static void initializeBedrock(RockSolidNode& node);
    static void initializeConstructA(RockSolidNode& node);
    static void initializeConstructB(RockSolidNode& node);
    static void initializeConstructC(RockSolidNode& node);

    static int needsGround;
    static int isGround;
    static int needsVertical;
    static int isVertical;
};
