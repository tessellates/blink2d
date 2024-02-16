#include "CellMoveProcessor.hpp"

OneWalkProcessor::OneWalkProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells) : CellMoveProcessor(cells) 
{
};


void OneWalkProcessor::processColumnsTopBottom(int threadId) {
    bool last = true;
    int startCol = (NoitaConfig::width / totalThreads) * threadId;
    int endCol = (threadId + 1 == totalThreads) ? NoitaConfig::width : (NoitaConfig::width / totalThreads) * (threadId + 1);
    for (int row = 0; row < NoitaConfig::height; ++row) {
        for (int col = startCol; col < endCol; ++col) {
            int index = row * NoitaConfig::width + col;
            cellWalk(index, 3, last);
        }
    }
    if (!last)
        lastIteration[threadId] = last;
}

void OneWalkProcessor::processColumnsBottomTop(int threadId) {
    bool last = true;
    int startCol = (NoitaConfig::width / totalThreads) * threadId;
    int endCol = (threadId + 1 == totalThreads) ? NoitaConfig::width : (NoitaConfig::width / totalThreads) * (threadId + 1);
    for (int row = NoitaConfig::height-1; row >= 0; --row) {
        for (int col = endCol-1; col >= startCol; --col) {
            int index = row * NoitaConfig::width + col;
            cellWalk(index, 4, last);
        }
    }
    if (!last)
        lastIteration[threadId] = last;
}

void OneWalkProcessor::processRowsLeftRight(int threadId) {
    bool last = true;
    int rowsPerThread = NoitaConfig::height / totalThreads;
    int startRow = rowsPerThread * threadId;
    int endRow = (threadId + 1 == totalThreads) ? NoitaConfig::height : startRow + rowsPerThread;
    
    int startIndex = startRow * NoitaConfig::width;
    int endIndex = endRow * NoitaConfig::width; // Exclusive

    for (int index = startIndex; index < endIndex; ++index) {
        cellWalk(index, 2, last);
    }
    if (!last)
        lastIteration[threadId] = last;
}


void OneWalkProcessor::processRowsRightLeft(int threadId) {
    bool last = true;
    int rowsPerThread = NoitaConfig::height / totalThreads;
    int startRow = rowsPerThread * threadId;
    int endRow = (threadId + 1 == totalThreads) ? NoitaConfig::height : startRow + rowsPerThread;
    
    int startIndex = startRow * NoitaConfig::width;
    int endIndex = endRow * NoitaConfig::width; // Exclusive

    for (int index = endIndex-1; index >= startIndex; --index) {
        cellWalk(index, 1, last);
    }
    if (!last)
        lastIteration[threadId] = last;
}

void OneWalkProcessor::cellWalk(int index, int direction, bool& last)
{
    if (!bs.test(index))
        return;
    if ((cells[index].walk & 0b111) != direction)
        return;
    int walkIndex = index + parseWalk(cells[index].walk);
    cells[index].walk >>= 3;
    if (last && cells[index].walk)
    {
        last = false;
    }
    if ((walkIndex < 0 || walkIndex >= NoitaConfig::numCells))
    {
        return;
    }
    if (cells[walkIndex].type == EMPTY)
    {
        bs.reset(walkIndex);
        bs.reset(index);
        std::swap(cells[index], cells[walkIndex]);
        return;
    }
    cells[index].walk = 0;
    bs.reset(index);
}

void OneWalkProcessor::update()
{
    if (!std::next_permutation(indexes.begin(), indexes.end()))
    {
        std::sort(indexes.begin(), indexes.end());
    }
    for (size_t r = 0; r < 4; r++)
    {
        size_t phaseIndex = indexes[r];
        std::vector<std::thread> threads;
        for (size_t i = 0; i < totalThreads; ++i) 
        {
            switch(phaseIndex)
            {
                case(0):
                    threads.emplace_back([this, i]() { this->processColumnsTopBottom(i); });
                    break;
                case(1):
                    threads.emplace_back([this, i]() { this->processColumnsBottomTop(i); });
                    break;
                case(2):
                    threads.emplace_back([this, i]() { this->processRowsLeftRight(i); });
                    break;
                case(3):
                    threads.emplace_back([this, i]() { this->processRowsRightLeft(i); });
                    break;
            }
        }
        for (std::thread& t : threads) {
            t.join();
        }
    }
    phase++;
    bs.set();
    bool finished = true;
    for (const bool& check : lastIteration)
    {
        if (!check)
        {
            finished = false;
            break;
        }
    }
    std::fill(lastIteration.begin(), lastIteration.end(), true);
    if (!finished)
    {
        update();       
    }
}
