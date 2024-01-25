#pragma once

#include "RenderEx.hpp"
#include <array>
#include <iostream>

template<int width, int height>
class RenderExManager
{
public:

    void renderSDL()
    {
        for(auto& ex : renderGrid)
        {
            if (ex.inUse)
                ex.render(renderer);
        }
    };

    RenderEx& getRenderAction(int x, int y)
    {
        return renderGrid[x + width*y];
    };

    void initialize(int x0, int y0, int size)
    {
        std::cout << "initialized at root:" << x0 << "," << y0 << std::endl;
        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                getRenderAction(x,y).updateQuad(x0 + x * size, y0 + y * size, size, size);
                getRenderAction(x,y).inUse = true;
            }
        }
    };

    RenderExManager() = default;
    ~RenderExManager() = default;   

    std::array<RenderEx, width*height> renderGrid;
    SDL_Renderer* renderer;
};
