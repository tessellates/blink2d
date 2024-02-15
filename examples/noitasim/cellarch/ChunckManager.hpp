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
    std::velocity<int> smartIndexes;
};