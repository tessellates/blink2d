#pragma once

#include "CellMeta.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>

class WalkCalculator
{
public:
    std::array<SmartCell, NoitaConfig::numCells>& cells;
    WalkCalculator(std::array<SmartCell, NoitaConfig::numCells>& cells);

    std::random_device rd;
    std::uniform_int_distribution<> distrib{1, 4};
    std::uniform_int_distribution<uint32_t> largeDistrib{0, 0xFFFFFFFF}; // 32-bit range
    std::mt19937 gen;

    int speed = 1;
    int direction = 0;

   void update();
};