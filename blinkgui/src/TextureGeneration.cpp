#include "TextureGeneration.hpp"
#include "Application.hpp"

BlinkTexture CreateGrid(float squareSize, float textureHeight, float textureWidth)
{
    auto renderer = blink2dgui::Application::instance()->getRenderer();
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
    for (float x = 0; x <= textureWidth+1; x += squareSize) {
        SDL_RenderDrawLine(renderer, x-1,  0, x-1, textureHeight);
        SDL_RenderDrawLine(renderer, x,  0, x, textureHeight);
    }
    for (float y =  0; y <= textureHeight+1; y += squareSize) {
        SDL_RenderDrawLine(renderer,  0, y-1, textureWidth, y-1);
        SDL_RenderDrawLine(renderer,  0, y, textureWidth, y);
    }

    // Reset the rendering target to the default
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);

    return BlinkTexture(gridTexture);
}
