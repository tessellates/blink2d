#pragma once

#include "rendering/BlinkTexure.hpp"

class RenderAction 
{
public:
    RenderAction(const BlinkTexture& texture, int x, int y);
    RenderAction(const BlinkTexture& texture, int x, int y, const SDL_RendererFlip& flip, const SDL_Point& center);
    render();
    
private:
    int x;
    int y;
    SDL_RendererFlip flip;
    double angle;
    SDL_Point center;
    BlinkTexture texture;
    
};
