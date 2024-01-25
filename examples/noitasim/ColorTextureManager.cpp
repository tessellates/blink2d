#include "ColorTextureManager.hpp"
#include <iostream>

ColorTextureManager::ColorTextureManager(SDL_Renderer* renderer, int width, int height)
    : renderer_(renderer), textureWidth_(width), textureHeight_(height) {}

SDL_Texture* ColorTextureManager::GetTexture(const ImVec4& color) 
{
    return CreateTexture(color);
    /*
    auto it = textureMap_.find(color);
    if (it != textureMap_.end()) {
        // Texture already exists for this color, return it
        return it->second;
    } else {
        // Texture does not exist, create it
        SDL_Texture* newTexture = CreateTexture(color);
        textureMap_[color] = newTexture;
        return newTexture;
    }*/
}

SDL_Texture* ColorTextureManager::CreateTexture(const ImVec4& color) {
    // Use the provided function to create a new texture
    SDL_Texture* colorTexture = CreateColorTextureBasic(renderer_, color, textureWidth_, textureHeight_);
    return colorTexture;
}

