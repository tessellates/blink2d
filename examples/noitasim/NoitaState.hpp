#pragma once

#include "CellMeta.hpp"
#include "NoitaConfig.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>

//#define USE_NOINLINE

#ifdef USE_NOINLINE
#define NOINLINE_ATTR __attribute__((noinline))
#else
#define NOINLINE_ATTR
#endif

class NoitaState {
public:
    NoitaState();

    std::array<Cell, NoitaConfig::numCells> cells;
    std::array<Cell, NoitaConfig::numCells> cellsOdd;
    std::array<SmartCell, NoitaConfig::numCells> simpleCells;
    std::array<SmartCell, NoitaConfig::numCells> simpleCellsReversed;
    bool odd = true;
    bool phase = false;

    float gravity = 0.1;
    float dragCoefficient = 0.01;

    NOINLINE_ATTR float computeVelocity(float velocity, float mass);
    int index(int x, int y) const;
    NOINLINE_ATTR void setSand(int x, int y);
    NOINLINE_ATTR void updateSwaps(int x, int y);
    NOINLINE_ATTR void updateVelocity(Cell& cell);
    NOINLINE_ATTR void update();
    NOINLINE_ATTR void swapCells(Cell& lcell, Cell& rcell);

    void testSpawn(int n = NoitaConfig::numCells/3)
    {
        cells.fill({CellType::EMPTY});
        for (int i = 0; i < n; ++i)
        {
            cells[i] = {CellType::SAND, {0,0}};
            cellsOdd[i] = {CellType::SAND, {0,0}};
        }
    }

    void randomTestSpawn()
    {
        int n = NoitaConfig::numCells;
        testSpawn(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis2(0, cells.size()-1);
        // Shuffle the array using Fisher-Yates algorithm
        for (size_t i = cells.size() - 1; i > 0; --i) {
            std::uniform_int_distribution<> dis(0, i);
            size_t j = dis(gen);
            std::swap(cells[i], cells[j]);
            simpleCells[i].walk = dis2(gen);
        }

    }

    void random_updater()
    {
        const bool targetOdd = odd;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, cells.size()-1);
        Cell empty;
        Cell sand {SAND};
        size_t j;
        for (size_t i = 0; i < cells.size(); ++i)
        {
            if (targetOdd)
            {
                if (cells[i].type != EMPTY)
                {
                    j = dis(gen);
                    cellsOdd[j] = std::move(cells[i]);
                    cellsOdd[i] = std::move(cells[j]);
                    //cellsOdd[dis(gen)] = std::move(cells[i]);
                    //cells[i] = sand;
                    //std::swap(cells[i], cellsOdd[dis(gen)]);
                }                
            }
            else
            {
                if (cellsOdd[i].type != EMPTY)
                {
                    j = dis(gen);
                    cells[j] = std::move(cellsOdd[i]);
                    cells[i] = std::move(cellsOdd[j]);
                    //std::swap(cells[dis(gen)], cellsOdd[i]);

                    //cells[dis(gen)] = std::move(cellsOdd[i]);
                    //cellsOdd[i] = sand;
                }
            }
        }
        odd = !targetOdd;
    }

    void random_updater_single()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, cells.size()-1);
        Cell empty;
        Cell sand {SAND};
        for (size_t i = 0; i < cells.size(); ++i)
        {
        
            if (cells[i].type != EMPTY)
            {
                std::swap(cells[i], cells[dis(gen)]);
            }
        }
    }

    void random_updater_simple()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, simpleCells.size() - 1);
        int x = dis(gen);
        for (size_t i = 0; i < simpleCells.size(); ++i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }

        x = dis(gen);/*
        for (size_t i = 0; i < simpleCells.size(); ++i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }*/

        return;

        for (size_t i = simpleCells.size()-1; i > 0; --i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }
    }

    void random_copy_updater_simple()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, simpleCells.size() - 1);
        int x = dis(gen);
        for (size_t i = 0; i < simpleCells.size(); ++i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }

        x = dis(gen);/*
        for (size_t i = 0; i < simpleCells.size(); ++i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }*/

        for (size_t i = simpleCells.size()-1; i > 0; --i)
        {
            simpleCells[i].walk += x;
            std::swap(simpleCells[i], simpleCells[simpleCells[i].walk % simpleCells.size()]);
        }
    }
};
