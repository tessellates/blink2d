#pragma once

#include <array>
#include <numeric>
#include <iostream>
#include <SDL.h>
#include <iostream>
#include "CircularBuffer.hpp"

class SDLTimer {
public:
    SDLTimer() = default;
    SDLTimer(const std::string& message) : message(message) {};
    
    void timeStart()
    {
        tickStart = SDL_GetTicks(); // Time of the last update call
    }

    void timeEnd()
    {
        averageTime.add(SDL_GetTicks()-tickStart);
        if (averageTime.head == 29)
        {
            std::cout << message << std::endl;
            std::cout << "timing:" << averageTime.getAverage() << std::endl;
        }
    }

    CircularBuffer<float,60> averageTime;
    std::string message;
    Uint32 tickStart;
};
