#pragma once

#include "BlinkTexture.hpp"
#include "Transform.hpp"
#include <optional>

class RenderAction 
{
public:
    RenderAction(int x, int y, const BlinkTexture& texture);
    RenderAction(int x, int y, const BlinkTexture& texture, double angle, const SDL_Point& center, const SDL_RendererFlip& flip);
    RenderAction(const Transform& transform, const BlinkTexture& texture);
    void render();
    
private:
    int x;
    int y;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    std::optional<SDL_Rect> clip;
    std::optional<SDL_Point> center;
    BlinkTexture texture;
};
