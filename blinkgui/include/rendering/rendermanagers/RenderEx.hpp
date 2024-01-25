#pragma once

#include "BlinkTexture.hpp"
#include "Transform.hpp"
#include <iostream>

class RenderEx
{
public:
    void render(SDL_Renderer*, SDL_Rect*);
    void render(SDL_Renderer*);
    void updatePosition(const Transform&);
    void updateTexture(const BlinkTexture&);
    void updateQuad(int x, int y, int w, int h);
    
    bool inUse = false;
public:
    SDL_Rect quad;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    SDL_Texture* texture;
};