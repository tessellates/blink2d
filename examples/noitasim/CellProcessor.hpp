#pragma once

#include "CellMeta.hpp"
#include "NoitaConfig.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <random>

class CellProcessor 
{
public:
    CellProcessor()
    {
        gen = std::mt19937(rd());
    }
    std::array<SmartCell, NoitaConfig::numCells> simpleCells;
    int speed = 1;

    int phase = 1;
    bool phasing = true;
    
    int direction = 3;

    std::random_device rd;
    std::uniform_int_distribution<> distrib{1, 4};
    std::uniform_int_distribution<uint32_t> largeDistrib{0, 0xFFFFFFFF}; // 32-bit range
    std::mt19937 gen;

    void update()
    {
        switch(phase)
        {
            case(0):
                for (size_t i = NoitaConfig::numCells-1; i > 0; --i)
                {
                    cellWalk(i);
                }
                break;
            case(1):
                for (size_t i = 0; i < NoitaConfig::numCells; ++i)
                {
                    cellWalk(i);
                }
                break;
            case(2):
                for (int y = 0; y < NoitaConfig::height; ++y) {
                    for (int x = NoitaConfig::width - 1; x >= 0; --x) {
                        cellWalk(y *  NoitaConfig::width + x);
                    }
                }
                break;
            case(3):
                for (int x = 0; x < NoitaConfig::width; ++x) {
                    for (int y = NoitaConfig::height - 1; y >= 0; --y) {
                        cellWalk(y *  NoitaConfig::width + x);
                    }
                }
                break;
        }
        if (phasing)
        {
            phase++;
            phase %= 2;
        }
    }

    void updateWalk()
    {
        int random = distrib(gen);
        for (size_t i = 0; i < NoitaConfig::numCells; ++i)
        {
            if (i < (NoitaConfig::height-1)*NoitaConfig::width && i > NoitaConfig::width && i % NoitaConfig::width != 0 && i % NoitaConfig::width != NoitaConfig::width - 1)
            {
                if (simpleCells[i].type != EMPTY)
                {
                    simpleCells[i].checked = false;
                    if (direction)
                    {
                        for (int j = 0; j < speed; ++j)
                        {
                            simpleCells[i].walk <<= 3;
                            switch(direction)
                            {
                                case(1):
                                case(2):
                                case(3):
                                case(4):
                                    simpleCells[i].walk += direction;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    else
                    {
                        uint32_t largeRandom = largeDistrib(gen);
                        for (int j = 0; j < speed; ++j) 
                        {
                            // Extract 4 bits and adjust the range
                            uint32_t smallRandom = (largeRandom >> (j * 3)) & 0xF; // Get 4 bits
                            //std::cout << smallRandom << std::endl;
                            smallRandom = smallRandom % 4 + 1; // Adjust range from 1 to 4

                            // Use smallRandom as needed
                            simpleCells[i].walk <<= 3;
                            simpleCells[i].walk += smallRandom;
                        }
                    }
                    /*
                    for (int j = 0; j < speed; ++j)
                    {
                        
                        simpleCells[i].walk <<= 3;
                        if (direction)
                        {
                            if (direction < 5)
                            {
                                simpleCells[i].walk += direction;
                            }
                            else
                            {
                                switch(direction)
                                {
                                    case(5):
                                        simpleCells[i].walk += 1+(random +(i*i))%4;
                                        break;
                                    case(6):
                                        simpleCells[i].walk += 1+(random+ (i*i*j))%4;
                                        break;
                                    case(7):
                                        simpleCells[i].walk += 1+ (random + (i << j))%4;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                        else
                        {
                            //simpleCells[i].walk += distrib(gen);
                        }
                    }*/
                }
            }
        }
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

    void testSpawn(int n = NoitaConfig::numCells/2)
    {
        simpleCells.fill({0, 0});
        simpleCells.fill({0, 0});
        for (int i = 0; i < n; ++i)
        {
            simpleCells[i] = {0, 1};
        }
    }

    void testSpawn2(int n = NoitaConfig::width/3)
    {
        simpleCells.fill({0, 0});
        simpleCells.fill({0, 0});
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                simpleCells[i+j*NoitaConfig::width] = {0, 1};
        }
    }


    void randomTestSpawn()
    {
        int n = NoitaConfig::numCells/2;
        testSpawn(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis2(0, NoitaConfig::numCells-1);
        // Shuffle the array using Fisher-Yates algorithm
        for (size_t i = NoitaConfig::numCells - 1; i > 0; --i) {
            std::uniform_int_distribution<> dis(0, i);
            size_t j = dis(gen);
            std::swap(simpleCells[i], simpleCells[j]);
        }
    }

    void cellWalk(int index, int depth = 0)
    {
        if (index < 0 || index >= NoitaConfig::numCells)
        {
            return;
        }
        simpleCells[index].checked = true;
        if (!simpleCells[index].walk)
        {
            return;
        }
        if (depth)
        {
            //triggerWalk(index, depth);
        }
        int walkIndex = index + parseWalk(simpleCells[index].walk);
        if ((walkIndex < 0 || walkIndex >= NoitaConfig::numCells) || (simpleCells[walkIndex].type != EMPTY && (simpleCells[walkIndex].walk == 0 || simpleCells[walkIndex].checked)))
        {
            if (!(walkIndex < 0 || walkIndex >= NoitaConfig::numCells) && depth)
            {
                simpleCells[index].type++;
            }
            simpleCells[index].walk = 0;
            return;
        }
        if (simpleCells[walkIndex].type == EMPTY)
        {
            std::swap(simpleCells[index], simpleCells[walkIndex]);
            simpleCells[walkIndex].walk >>= 3;
            cellWalk(walkIndex, depth+1);
            return;
        }
        
        cellWalk(walkIndex);
        simpleCells[index].checked = false;
        cellWalk(index);
    }

    void triggerWalk(int index, int depth)
    {
        switch (simpleCells[index].walk & 0b111) 
        {
            case 1:
                cellWalk(index + parseWalk(2), depth-1);
                cellWalk(index + parseWalk(3), depth-1);
                cellWalk(index + parseWalk(4), depth-1);
                break;
            case 2:
                cellWalk(index + parseWalk(1), depth-1);
                cellWalk(index + parseWalk(3), depth-1);
                cellWalk(index + parseWalk(4), depth-1);
                break;
            case 3:
                cellWalk(index + parseWalk(2), depth-1);
                cellWalk(index + parseWalk(1), depth-1);
                cellWalk(index + parseWalk(4), depth-1);
                break;
            case 4:
                cellWalk(index + parseWalk(2), depth-1);
                cellWalk(index + parseWalk(3), depth-1);
                cellWalk(index + parseWalk(1), depth-1);
                break;
            default:
                std::cout << "Invalid input\n";
        }
    }
};

