#include "RenderEx.hpp"

void RenderEx::render(SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_RenderCopyEx(renderer, texture, clip, &quad, angle, nullptr, flip);
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
    quad.width *= transform.scale.x;
    quad.height *= transform.scale.y;
}

void RenderEx::updateTexture(const BlinkTexture& texture)
{
    quad.width = texture.m_width;
    quad.height = texture.m_height;
    texture = m_texture;
}