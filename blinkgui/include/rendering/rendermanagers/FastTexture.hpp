#pragma once

#include <SDL.h>
#include <vector>
#include <cstdint>
#include <array>

template<int width_, int height_>
class FastTexture {
public:
    FastTexture() = default;

    void initialize(SDL_Renderer* renderer)
    {
        renderer_ = renderer;
        texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width_, height_);
    };

    ~FastTexture() {
        SDL_DestroyTexture(texture_);
    }

    // Method to set a pixel in the buffer
    void setPixel(int x, int y, Uint32 color) {
        pixels_[y * width_ + x] = color;
    }

    // Method to update the SDL texture with the buffer's content
    void updateTexture() {
        void* pixels;
        int pitch;
        SDL_LockTexture(texture_, NULL, &pixels, &pitch);
        std::memcpy(pixels, pixels_.data(), pixels_.size() * sizeof(Uint32));
        SDL_UnlockTexture(texture_);
    }

    // Method to render the texture
    void render(int x, int y) {
        SDL_Rect dstRect = { x, y, width_ * scale, height_ * scale};
        SDL_RenderCopy(renderer_, texture_, NULL, &dstRect);
    }

    void render(SDL_Rect* quad) {
        SDL_RenderCopy(renderer_, texture_, NULL, quad);
    }

public:
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;
    int scale = 1;
    std::array<Uint32, width_*height_> pixels_;
};