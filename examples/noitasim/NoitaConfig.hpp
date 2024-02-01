#pragma once

struct NoitaConfig
{
    static constexpr int cellSize = 1;
    //static constexpr int height = 2000 / cellSize;
    //static constexpr int width = 2000 / cellSize;
    static constexpr int width = 1312 / cellSize;
    static constexpr int height = 945 / cellSize;
    static constexpr int numCells = width*height;
};