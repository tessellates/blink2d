#include "NoitaState.hpp"

NoitaState::NoitaState()
{
#ifdef USE_NOINLINE
    std::cout << "WARNING NO INLINING" << std::endl;
#endif
}

float NoitaState::computeVelocity(float velocity, float mass)
{
    if (velocity == 0)
    {
        return gravity;
    }
    float dragForce = dragCoefficient * velocity * velocity;
    if (dragForce / mass > velocity + gravity)
    {
        return 0;
    }
    dragForce *= velocity/std::abs(velocity);

    return velocity + gravity - dragForce / mass;
}

int NoitaState::index(int x, int y) const {
    return y * NoitaConfig::width + x;
}

void NoitaState::setSand(int x, int y) {
    cells[index(x, y)] = {CellType::SAND, {0,0}};
    cells[index(x, y)].phase = !phase;
}

void NoitaState::updateSwaps(int x, int y)
{
    int cellIndex = index(x,y);
    if (cells[cellIndex].moveUnits.y > 5)
        std::cout << "WHAT THE FUCKKK" << std::endl;
    while (cells[cellIndex].moveUnits.y >= 1)
    {
        ++y;
        int downIndex = index(x, y);
        if (y < NoitaConfig::height)
        {
            if (cells[downIndex].type == SAND)
            {
                cells[cellIndex].moveUnits.y = 0;
                continue;
            }
            cells[cellIndex].moveUnits.y--;
            std::swap(cells[cellIndex], cells[downIndex]);
            //swapCells(cells[cellIndex], cells[downIndex]);
            cellIndex = downIndex;
        }
        else
        {
            cells[cellIndex].moveUnits.y = 0;
            cells[cellIndex].velocity.y = 0;
        }
    }
}

void NoitaState::updateVelocity(Cell& cell)
{
    cell.velocity.y = computeVelocity(cell.velocity.y, cell.getMass());
    cell.moveUnits += cell.velocity;
}

void NoitaState::update()
{
    phase = !phase;
    for (int x = 0; x < NoitaConfig::width; ++x)
    {
        for (int y = NoitaConfig::height-1; y >= 0; --y)
        {
            auto& cell = cells[index(x,y)];
            /*
            if (cell.phase != phase || cell.type == EMPTY)
            {
                continue;
            }*/
            //cell.phase = !phase;
            updateVelocity(cell);
            updateSwaps(x, y);
        }
    }
}

void NoitaState::swapCells(Cell& lcell, Cell& rcell)
{
    //rcell = std::move(lcell);
    //lcell.type = EMPTY;
    
    // exclude from the current phase
    //lcell.phase = !phase;
    //rcell.phase = !phase;
    std::swap(lcell, rcell);
}
