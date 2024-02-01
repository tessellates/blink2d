
#include "WalkCalculator.hpp"


WalkCalculator::WalkCalculator(std::array<SmartCell, NoitaConfig::numCells>& cells) : cells(cells)
{
    gen = std::mt19937(rd());
}

void WalkCalculator::update()
{
    for (size_t i = 0; i < NoitaConfig::numCells; ++i)
    {
        if (i < (NoitaConfig::height-1)*NoitaConfig::width && i > NoitaConfig::width && i % NoitaConfig::width != 0 && i % NoitaConfig::width != NoitaConfig::width - 1)
        {
            if (cells[i].type != EMPTY)
            {
                cells[i].checked = false;
                if (direction)
                {
                    for (int j = 0; j < speed; ++j)
                    {
                        cells[i].walk <<= 3;
                        switch(direction)
                        {
                            case(1):
                            case(2):
                            case(3):
                            case(4):
                                cells[i].walk += direction;
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
                        cells[i].walk <<= 3;
                        cells[i].walk += smallRandom;
                    }
                }
    
            }
        }
    }
}
