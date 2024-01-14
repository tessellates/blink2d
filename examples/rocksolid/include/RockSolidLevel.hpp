#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

#include "RockSolidNode.hpp"
// Forward declaration of classes used in the header

struct RockSolidLevelLayoutNode
{
    RockSolidNodeType type;// = 0;
    int gemCount;
};

struct RockSolidLevel
{
    int budget;
    int gemTarget;
    int width;
    int height;
    std::vector<RockSolidLevelLayoutNode> layoutNodes;
};



inline RockSolidLevel initializeRockSolidLevel() {
    RockSolidLevel level;
    level.budget = 0; // Set budget as needed
    level.gemTarget = 0; // Set gem target as needed
    level.height = 7;
    level.width = 7;

    const int emptyCount = 20;
    const int depositCount = 3;

    // Initialize layoutNodes with empty vectors
    level.layoutNodes.resize(level.height * level.width);

    // Randomly assign GEM_DEPOSIT nodes
    srand(time(NULL));
    for (int i = 0; i < depositCount; ++i) {
        int x,y;

        x = rand() % level.width;
        y = rand() % level.height;
     
        level.layoutNodes[x + y * level.width].type = GEM_DEPOSIT;
        level.layoutNodes[x + y * level.width].gemCount = 1; // Set gem count as needed
    }

    // Assign EMPTY nodes
    int emptyAssigned = 0;
    while (emptyAssigned < emptyCount) {
        int x = rand() % level.width;
        int y = rand() % level.height;

        if (level.layoutNodes[x + y * level.width].type == EMPTY) {
            emptyAssigned++;
        } else {
            level.layoutNodes[x + y * level.width].type = EMPTY;
            level.layoutNodes[x + y * level.width].gemCount = 0;
            emptyAssigned++;
        }
    }

    // Fill the rest with ROCK and DIRT
    for (int x = 0; x < level.width; ++x) {
        for (int y = 0; y < level.height; ++y) {
            if (level.layoutNodes[x + y * level.width].type == 0) 
            {
                // Decide between ROCK and DIRT
                level.layoutNodes[x + y * level.width].type = (rand() % 2 == 0) ? ROCK : DIRT;
                level.layoutNodes[x + y * level.width].gemCount = 0;
            }
        }
    }

    return level;
}