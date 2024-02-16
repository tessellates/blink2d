#pragma once

#include "CRTP.hpp"
#include "CellMeta.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>
#include <mutex>
#include <bitset>
#include <thread>
#include <vector>

template <typename _Derived>
class CellMoveProcessor : public CRTP<_Derived>
{
public:
/*
    CellMoveProcessor(std::vector<SmartCell>& cells) : cells(cells) {
        totalThreads = std::min(std::thread::hardware_concurrency(), NoitaConfig::maxThreads);
        lastIteration = std::vector<bool>(totalThreads, true);
    };*/

    CellMoveProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells) : cells(cells) {
        totalThreads = std::min(std::thread::hardware_concurrency(), NoitaConfig::maxThreads);
        lastIteration = std::vector<bool>(totalThreads, true);
    };
    int totalThreads;
    std::vector<bool> lastIteration;
    std::vector<size_t> indexes = {0, 1, 2, 3};
    std::bitset<NoitaConfig::numCells> bs;
    std::array<SmartCell, NoitaConfig::numCells>& cells;
    int speed = 1;
    int phase = 1;
    bool phasing = true;
    bool parallel = false;
    int itt = 0;
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
    //PhasedWalkProcessor(std::vector<SmartCell>& cells);
    PhasedWalkProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells);
    void update();
    void updateParallel();
    void cellWalk(int index, int = 0);
    void cellWalkThread(int index, int = 0, int = 0);
};


class OneWalkProcessor : public CellMoveProcessor<OneWalkProcessor>
{
public:
    //OneWalkProcessor(std::vector<SmartCell>& cells);
    OneWalkProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells);
    void update();
    void cellWalk(int index, int direction, bool&);

    void processRowsRightLeft(int threadId);
    void processRowsLeftRight(int threadId);
    void processColumnsTopBottom(int threadId);
    void processColumnsBottomTop(int threadId);
};

/*
class PathProcessor : public CellMoveProcessor<PathProcessor>
{
public:
    PathProcessor(std::vector<SmartCell>& cells);
    void update();
    void cellWalk(int index, int direction, bool&);

    void processRowsRightLeft(int threadId);
    void processRowsLeftRight(int threadId);
    void processColumnsTopBottom(int threadId);
    void processColumnsBottomTop(int threadId);
};*/