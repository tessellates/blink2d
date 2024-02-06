#pragma once

#include "CRTP.hpp"
#include "CellMeta.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>
#include <mutex>
#include <unordered_set>

class Chunck
{
public:
    std::array<int, NoitaConfig::numCells> smartIndexes;
    std::array<int, 6> indexHead;
};