#include "CellMoveProcessor.hpp"

PhasedWalkProcessor::PhasedWalkProcessor(std::array<SmartCell, NoitaConfig::numCells>& cells) : CellMoveProcessor(cells) {};

void PhasedWalkProcessor::update()
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
    }
    if (phasing)
    {
        phase++;
        phase %= 2;
    }
}

void PhasedWalkProcessor::cellWalk(int index, int depth)
{
    if (index < 0 || index >= NoitaConfig::numCells)
    {
        return;
    }
    cells[index].checked = true;
    if (!cells[index].walk)
    {
        return;
    }
    int walkIndex = index + parseWalk(cells[index].walk);
    if ((walkIndex < 0 || walkIndex >= NoitaConfig::numCells) || (cells[walkIndex].type != EMPTY && (cells[walkIndex].walk == 0 || cells[walkIndex].checked)))
    {
        if (!(walkIndex < 0 || walkIndex >= NoitaConfig::numCells) && depth)
        {
            cells[index].type++;
        }
        cells[index].walk = 0;
        return;
    }
    if (cells[walkIndex].type == EMPTY)
    {
        std::swap(cells[index], cells[walkIndex]);
        cells[walkIndex].walk >>= 3;
        cellWalk(walkIndex, depth+1);
        return;
    }
    
    cellWalk(walkIndex);
    cells[index].checked = false;
    cellWalk(index);
}
