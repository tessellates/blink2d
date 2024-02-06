#include "CellManager.hpp"


CellManager::CellManager() : move(cells), walk(cells) {};

void CellManager::updateCells()
{
    move.update();
}

void CellManager::updateMove()
{
    walk.update();
}

void CellManager::testSpawn(int n)
{
    cells.fill({0, 0});
    for (int i = 0; i < n; ++i)
    {
        cells[i] = {0, 1};
    }
}

void CellManager::randomTestSpawn()
{
    int n = NoitaConfig::numCells/5;
    testSpawn(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis2(0, NoitaConfig::numCells-1);
    // Shuffle the array using Fisher-Yates algorithm
    for (size_t i = NoitaConfig::numCells - 1; i > 0; --i) {
        std::uniform_int_distribution<> dis(0, i);
        size_t j = dis(gen);
        std::swap(cells[i], cells[j]);
    }
}