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
    std::vector<std::vector<RockSolidLevelLayoutNode>> layoutNodes;
};



inline RockSolidLevel initializeRockSolidLevel() {
    RockSolidLevel level;
    level.budget = 0; // Set budget as needed
    level.gemTarget = 0; // Set gem target as needed

    // Constants for node type counts
    const int numRows = 7;
    const int numColumns = 7;
    const int emptyCount = 20;
    const int depositCount = 3;

    // Initialize layoutNodes with empty vectors
    level.layoutNodes.resize(numRows, std::vector<RockSolidLevelLayoutNode>(numColumns));

    // Randomly assign GEM_DEPOSIT nodes
    srand(time(NULL));
    for (int i = 0; i < depositCount; ++i) {
        int r, c;

        r = rand() % numRows;
        c = rand() % numColumns;
     
        level.layoutNodes[r][c].type = GEM_DEPOSIT;
        level.layoutNodes[r][c].gemCount = 1; // Set gem count as needed
    }

    // Assign EMPTY nodes
    int emptyAssigned = 0;
    while (emptyAssigned < emptyCount) {
        int r = rand() % numRows;
        int c = rand() % numColumns;

        if (level.layoutNodes[r][c].type == EMPTY) {
            emptyAssigned++;
        } else {
            level.layoutNodes[r][c].type = EMPTY;
            level.layoutNodes[r][c].gemCount = 0;
            emptyAssigned++;
        }
    }

    // Fill the rest with ROCK and DIRT
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numColumns; ++c) {
            if (level.layoutNodes[r][c].type == 0) 
            {
                // Decide between ROCK and DIRT
                level.layoutNodes[r][c].type = (rand() % 2 == 0) ? ROCK : DIRT;
                level.layoutNodes[r][c].gemCount = 0;
            }
        }
    }

    return level;
}