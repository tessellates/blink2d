#pragma once

#include <array>
#include <numeric>
#include <iostream>

template<typename T,int N>
class CircularBuffer {
public:
    CircularBuffer() = default;

    void init(T value)
    {
        buffer.fill(value);
        sum = value * buffer.size();
    }

    void add(T value) 
    {
        if (std::isnan(value) || std::isinf(value))
        {
            return;
        }
        sum -= buffer[head];
        buffer[head] = value;
        sum += value;
        head = (head + 1) % buffer.size();
    }

    T getAverage() const 
    {
        return sum / buffer.size();
    }

    std::array<T,N> buffer;
    size_t head = 0;
    float sum;
};
