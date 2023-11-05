#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "imgui.h"

inline SDL_Texture* CreateBackgroundTexture(SDL_Renderer* renderer, float spacing, float textureHeight, float textureWidth)
{
    // Create a texture that will be used as a render target
    SDL_Texture* gridTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

    // Set the texture as the current rendering target
    SDL_SetRenderTarget(renderer, gridTexture);

    // Set blend mode to blend for transparency
    SDL_SetTextureBlendMode(gridTexture, SDL_BLENDMODE_BLEND);

    // Clear the texture with a transparent color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Draw the grid lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White lines, or any color you choose
    for (float x = spacing/2; x < textureWidth; x += spacing) {
        SDL_RenderDrawLine(renderer, x-1,  spacing/2, x-1, textureHeight -  spacing/2);
        SDL_RenderDrawLine(renderer, x,  spacing/2, x, textureHeight -  spacing/2);
    }
    for (float y =  spacing/2; y < textureHeight; y += spacing) {
        SDL_RenderDrawLine(renderer,  spacing/2, y-1, textureWidth -  spacing/2, y-1);
        SDL_RenderDrawLine(renderer,  spacing/2, y, textureWidth -  spacing/2, y);
    }

    // Reset the rendering target to the default
    SDL_SetRenderTarget(renderer, NULL);
    return gridTexture;
}
