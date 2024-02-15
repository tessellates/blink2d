#include "CellMoveProcessor.hpp"
#include <thread>
#include <vector>

PhasedWalkProcessor::PhasedWalkProcessor(std::vector<SmartCell>& cells) : CellMoveProcessor(cells) 
{
};

void PhasedWalkProcessor::update()
{
    if (parallel)
    {
        updateParallel();
        return;
    }
    switch(phase)
    {
        case(0):
            for (size_t i =  NoitaConfig::numCells-1; i > 0; --i) {
                this->cellWalk(i);
            }
            break;
        case(1):
            for (size_t i = 0; i < NoitaConfig::numCells; ++i) {
                this->cellWalk(i);
            }
            break;
    }
    if (phasing)
    {
        phase++;
        phase %= 2;
    }
}


void PhasedWalkProcessor::updateParallel()
{
    auto worker = [this](size_t start, size_t end, int id) {
        for (size_t i = start; i < end; ++i) {
            this->cellWalkThread(i,0, id);
        }
    };

    auto worker2 = [this](size_t start, size_t end, int id) {
        for (size_t i = end-1; i > 0; --i) {
            this->cellWalkThread(i,0, id);
        }
    };


    const size_t numThreads = 6; // Number of tasks
    const size_t chunkSize = NoitaConfig::numCells / numThreads;
    std::vector<std::thread> threads;

    switch(phase)
    {
        case(0):
            for (size_t i = 0; i < numThreads; ++i) 
            {
                size_t start = i * chunkSize;
                size_t end = (i == numThreads - 1) ? NoitaConfig::numCells : start + chunkSize;
                threads.emplace_back(worker, start, end, i+1);
            }
            for (std::thread& t : threads) {
                t.join();
            }
            break;
        case(1):
            for (size_t i = 0; i < numThreads; ++i) 
            {
                size_t start = i * chunkSize;
                size_t end = (i == numThreads - 1) ? NoitaConfig::numCells : start + chunkSize;
                threads.emplace_back(worker2, start, end, i+1);
            }
            for (std::thread& t : threads) {
                t.join();
            }
            break;
    }
    if (phasing)
    {
        phase++;
        phase %= 2;
    }
}

void PhasedWalkProcessor::cellWalk(int index, int depth)
{
    if (index < 0 || index >= NoitaConfig::numCells) // || cells[index].type == EMPTY )
    {
        return;
    }
    if (cells[index].checked)
        return;
    if (!cells[index].walk)
    {
        return;
    }
    cells[index].checked = 1;
    int walkIndex = index + parseWalk(cells[index].walk);
    if ((walkIndex < 0 || walkIndex >= NoitaConfig::numCells) || (cells[walkIndex].type != EMPTY && (cells[walkIndex].walk == 0 || cells[walkIndex].checked)))
    {
        if (!(walkIndex < 0 || walkIndex >= NoitaConfig::numCells) && depth)
        {
            //cells[index].type++;
        }
        cells[index].walk = 0;
        return;
    }
    if (cells[walkIndex].type == EMPTY)
    {
        cells[index].checked = 0;
        std::swap(cells[index], cells[walkIndex]);
        cells[walkIndex].walk >>= 3;
        cellWalk(walkIndex, depth+1);
        return;
    }
    
    cellWalk(walkIndex);
    cells[index].checked = 0;
    cellWalk(index);
}

void PhasedWalkProcessor::cellWalkThread(int index, int depth, int id)
{
    if (index < 0 || index >= NoitaConfig::numCells)
        return;
    if (cells[index].checked && cells[index].checked != id)
        return;
    if (!cells[index].walk)
        return;
    cells[index].checked = id;
    int walkIndex = index + parseWalk(cells[index].walk);
    if (walkIndex >= 0 && walkIndex < NoitaConfig::numCells && !cells[walkIndex].checked)
    {
        cells[walkIndex].checked = id;
    }
    else
    {
        cells[index].walk = 0;
        cells[index].checked = 0;
        return;
    }
    if (cells[index].checked != id)
    {
        std::cout << "break 1" << std::endl;
    }
    if (cells[walkIndex].type != EMPTY && (cells[walkIndex].walk == 0))
    {
        if (!(walkIndex < 0 || walkIndex >= NoitaConfig::numCells) && depth)
        {
            //cells[index].type++;
        }
        cells[index].walk = 0;
        cells[index].checked = 0;
        return;
    }
    if (cells[index].checked != id)
    {
        std::cout << "break 2" << std::endl;
    }
    if (cells[walkIndex].type == EMPTY)
    {
        if (cells[index].checked != id || cells[walkIndex].checked != id)
        {
            //std::cout << "race :" << cells[index].checked << "vs" << cells[walkIndex].checked << std::endl;
        }
        std::swap(cells[index], cells[walkIndex]);
        cells[walkIndex].walk >>= 3;
        cellWalkThread(walkIndex, depth+1, id);
        cells[index].checked = 0;
        //cells[walkIndex].checked = 0;
        return;
    }
    
    cellWalkThread(walkIndex, 0, id);
    cells[walkIndex].checked = 0;
    cellWalkThread(index, 0, id);
}
