#pragma once

#include <SDL.h>
#include <string>

class BlinkTexture {
public:
    BlinkTexture() = default;
    BlinkTexture(SDL_Renderer* renderer, SDL_Texture* texture);
    BlinkTexture(SDL_Texture* texture);
    BlinkTexture(SDL_Texture* texture, int width, int height);
    ~BlinkTexture();
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

public:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};

