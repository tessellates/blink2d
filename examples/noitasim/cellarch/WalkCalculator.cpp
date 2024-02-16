#include "WalkCalculator.hpp"

WalkCalculator::WalkCalculator(std::array<SmartCell, NoitaConfig::numCells>& cells) : cells(cells), numThreads(std::thread::hardware_concurrency()), chunkSize(NoitaConfig::numCells / numThreads)
{
    for (int i = 0; i < numThreads; ++i)
    {
        gens.emplace_back(rd());
    }
}

void WalkCalculator::update()
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? NoitaConfig::numCells : start + chunkSize;

        // Launch a thread for each chunk of work
        threads.emplace_back([this, start, end, i]() {
            this->update(start, end, i);
        });
    }

        // Wait for all threads to complete
    for (std::thread& t : threads) {
        t.join();
    }
}


void WalkCalculator::update(size_t start, size_t end, size_t id)
{
    for (size_t i = start; i < end; ++i)
    {
        if (i < (NoitaConfig::height-1)*NoitaConfig::width && i > NoitaConfig::width && i % NoitaConfig::width != 0 && i % NoitaConfig::width != NoitaConfig::width - 1)
        {
            if (cells[i].type != EMPTY)
            {
                cells[i].checked = false;
                if (direction)
                {
                    directionWalk(i);
                }
                else
                {
                    randomWalk(i, id);
                }
    
            }
        }
    }
}

void WalkCalculator::randomWalk(size_t index, size_t id)
{
    uint32_t largeRandom = largeDistrib(gens[id]);
    for (int j = 0; j < speed; ++j) 
    {
        // Extract 4 bits and adjust the range
        uint32_t smallRandom = (largeRandom >> (j * 3)) & 0b111; // Get 3 bits
        //std::cout << smallRandom << std::endl;
        smallRandom = smallRandom % 4 + 1; // Adjust range from 1 to 4

        // Use smallRandom as needed
        cells[index].walk <<= 3;
        cells[index].walk += smallRandom;
    }
    if (index%10 == 0)
    {
        if (false)
        {
            uint32_t largeRandom = largeDistrib(gens[id]);
            cells[index].walk = 0;
            for (int j = 0; j < 10; ++j) 
            {
                // Extract 4 bits and adjust the range
                uint32_t smallRandom = (largeRandom >> (j * 3)) & 0xF; // Get 4 bits
                //std::cout << smallRandom << std::endl;
                smallRandom = smallRandom % 4 + 1; // Adjust range from 1 to 4

                // Use smallRandom as needed
                cells[index].walk <<= 3;
                cells[index].walk += smallRandom;
            }
        }
    }
}

void WalkCalculator::directionWalk(size_t index)
{
    for (int j = 0; j < speed; ++j)
    {
        cells[index].walk <<= 3;
        switch(direction)
        {
            case(1):
            case(2):
            case(3):
            case(4):
                cells[index].walk += direction;
                break;
            default:
                break;
        }
    }
}