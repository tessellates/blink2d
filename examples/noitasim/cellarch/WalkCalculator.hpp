#pragma once

#include "CellMeta.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

class WalkCalculator
{
public:
    std::array<SmartCell, NoitaConfig::numCells>& cells;
    WalkCalculator(std::array<SmartCell, NoitaConfig::numCells>& cells);

    std::random_device rd;
    std::uniform_int_distribution<> distrib{1, 4};
    std::uniform_int_distribution<uint32_t> largeDistrib{0, 0xFFFFFFFF}; // 32-bit range

    std::vector<std::mt19937> gens;
    const size_t numThreads;
    const size_t chunkSize; 

    int speed = 3;
    int direction = 4;

   void update();
   void update(size_t start, size_t end, size_t id);
   void randomWalk(size_t index, size_t id = 0);
   void directionWalk(size_t index);
};