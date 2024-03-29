#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "imgui.h"
#include "rendering/BlinkTexture.hpp"
#include <vector>


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

    //SDL_RenderClear(renderer);

    // Reset the rendering target to the default
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    
    return gridTexture;
}

inline BlinkTexture CreateColorTexture(SDL_Renderer* renderer, const ImVec4& color, int textureWidth, int textureHeight) {
    // Create a texture that will be used as a render target
    SDL_Texture* colorTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

    // Set the texture as the current rendering target
    SDL_SetRenderTarget(renderer, colorTexture);

    // Set blend mode to blend for transparency
    SDL_SetTextureBlendMode(colorTexture, SDL_BLENDMODE_BLEND);

    // Convert ImGui color (0.0-1.0 range) to SDL color (0-255 range)
    SDL_SetRenderDrawColor(renderer, 
                           static_cast<Uint8>(color.x * 255), 
                           static_cast<Uint8>(color.y * 255), 
                           static_cast<Uint8>(color.z * 255), 
                           static_cast<Uint8>(color.w * 255));

    // Clear the texture with the specified color
    SDL_RenderClear(renderer);

    // Reset the rendering target to the default
    SDL_SetRenderTarget(renderer, NULL);
    return BlinkTexture(colorTexture);
}

inline SDL_Texture* CreateColorTextureBasic(SDL_Renderer* renderer, const ImVec4& color, int textureWidth, int textureHeight) {
    // Create a texture that will be used as a render target
    SDL_Texture* colorTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

    // Set the texture as the current rendering target
    SDL_SetRenderTarget(renderer, colorTexture);

    // Set blend mode to blend for transparency
    SDL_SetTextureBlendMode(colorTexture, SDL_BLENDMODE_NONE);

    // Convert ImGui color (0.0-1.0 range) to SDL color (0-255 range)
    SDL_SetRenderDrawColor(renderer, 
                           static_cast<Uint8>(color.x * 255), 
                           static_cast<Uint8>(color.y * 255), 
                           static_cast<Uint8>(color.z * 255), 
                           static_cast<Uint8>(color.w * 255));

    // Clear the texture with the specified color
    SDL_RenderClear(renderer);

    // Reset the rendering target to the default
    SDL_SetRenderTarget(renderer, NULL);
    return colorTexture;
}

inline SDL_Texture* CreateTextureFromFile(SDL_Renderer* renderer, const char* filePath) {
    // Load the image into an SDL_Surface
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
        return nullptr;
    }


    // Convert the surface to a texture
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // RGBA: 0,0,0,0 for full transparency

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_Log("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
    }

    // Set blend mode to blend for transparency
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Free the surface as it's no longer needed
    SDL_FreeSurface(surface);
    
    return texture;
}

inline std::vector<SDL_Texture*> CutTextureSheet(SDL_Renderer* renderer, SDL_Texture* spriteSheet, int textureWidth = 0) {
    std::vector<SDL_Texture*> sprites;

    // Get the width and height of the spriteSheet
    int sheetWidth, sheetHeight;
    SDL_QueryTexture(spriteSheet, nullptr, nullptr, &sheetWidth, &sheetHeight);

    if (textureWidth == 0)
    {
        textureWidth = sheetHeight;
    }

    int spriteCount = sheetWidth / textureWidth;

    for (int i = 0; i < spriteCount; ++i) {
        // Define the portion of the sprite sheet to capture
        SDL_Rect spriteRect = {i * textureWidth, 0, textureWidth, sheetHeight};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // RGBA: 0,0,0,0 for full transparency

        // Create a target texture (empty texture) to render to
        SDL_Texture* targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                                                      SDL_TEXTUREACCESS_TARGET, textureWidth, sheetHeight);
        if (!targetTexture) {
            continue; // Handle error
        }

        // Reset the rendering target
        SDL_SetRenderTarget(renderer, nullptr);

        // Important: Set the blend mode for transparency
        SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);

        // Set the target texture as the rendering target
        SDL_SetRenderTarget(renderer, targetTexture);

        // Clear with transparent color (critical for preserving transparency)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Fully transparent
        SDL_RenderClear(renderer);

              // Copy the sprite from the sprite sheet to the target texture
        SDL_RenderCopy(renderer, spriteSheet, &spriteRect, nullptr);

        // Reset the rendering target
        SDL_SetRenderTarget(renderer, nullptr);

        sprites.push_back(targetTexture);
    }

    return sprites;
}
