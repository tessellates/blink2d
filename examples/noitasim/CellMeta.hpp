#pragma once

#include "imgui.h"
#include <cstdlib> // for rand and srand
#include "SDL.h" // for rand and srand
#include <array> // for rand and srand
#include "NoitaConfig.hpp" // for rand and srand

enum CellType 
{
    EMPTY = 0,
    SAND,
    STONE,
    NumTypes // Keep this last
};

const float cellMasses[CellType::NumTypes] = {
    0.0f,    // Empty
    1.0f,    // Sand
    2.0f     // Stone
};

struct CellData 
{
    CellType type = EMPTY;
    ImVec2 velocity {0, 0};
    int variance = rand() % 2;
    float getMass() const 
    {
        return cellMasses[type];
    }
};

struct SmartCell 
{
    Uint32 walk = 0;
    Uint32 type = 0;
    Uint32 checked = 0;
    //bool checked = false;
    //CellData* cdata;
};


struct Cell 
{
    CellType type = EMPTY;
    ImVec2 velocity {0, 0};
    ImVec2 moveUnits {0, 0};
    int variance = rand() % 2;
    bool phase = false;

    float getMass() const {
        return cellMasses[type];
    }
};
