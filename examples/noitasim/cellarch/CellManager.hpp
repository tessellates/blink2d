#pragma once

#include "CellMeta.hpp"
#include "WalkCalculator.hpp"
#include "CellMoveProcessor.hpp"

class CellManager
{
public:
    CellManager();
    //std::vector<SmartCell> cells;
    std::array<SmartCell, NoitaConfig::numCells> cells;
    void updateCells();
    void updateMove();

    CellMoveProcessor<OneWalkProcessor> move;
    //CellMoveProcessor<PhasedWalkProcessor> move;
    WalkCalculator walk;

    void testSpawn(int n = NoitaConfig::numCells/2);

    void randomTestSpawn();
};