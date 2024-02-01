#pragma once

#include "CRTP.hpp"
#include "CellMeta.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>

template <typename _Derived>
class CellMoveProcessor : public CRTP<_Derived>
{
public:
    CellMoveProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells) : cells(cells) {};

    std::array<SmartCell, NoitaConfig::numCells>& cells;
    int speed = 1;
    int phase = 1;
    bool phasing = true;
    
    void update()
    {
        this->derived().update();
    }

    int parseWalk(int walk)
    {
        switch(walk & 0b111)
        {
            case(1):
                return 1;
            case(2):
                return -1;
            case(3):
                return -NoitaConfig::width;
            case(4):
                return NoitaConfig::width;
            default:
                return 0;
        }
    }
};

class PhasedWalkProcessor : public CellMoveProcessor<PhasedWalkProcessor>
{
public:
    PhasedWalkProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells);
    void update();
    void cellWalk(int index, int = 0);
};