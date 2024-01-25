#include "RenderEx.hpp"

void RenderEx::render(SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_RenderCopy(renderer, texture, nullptr, &quad);
    //SDL_RenderCopyEx(renderer, texture, clip, &quad, angle, nullptr, flip);
}

void RenderEx::render(SDL_Renderer* renderer)
{
    render(renderer, nullptr);
}

void RenderEx::updatePosition(const Transform& transform)
{
    quad.x = transform.position.x;
    quad.y = transform.position.y;
    angle = transform.rotation;
    flip = transform.flip;
    quad.w *= transform.scale.x;
    quad.h *= transform.scale.y;
}

void RenderEx::updateTexture(const BlinkTexture& texture)
{
    quad.w = texture.m_width;
    quad.h = texture.m_height;
    this->texture = texture.m_texture;
}

void RenderEx::updateQuad(int x, int y, int w, int h)
{
    quad.x = x;
    quad.y = y;
    quad.w = w;
    quad.h = h;
}