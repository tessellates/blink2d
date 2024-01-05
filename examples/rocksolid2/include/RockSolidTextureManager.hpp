#pragma once

#include "Application.hpp"
#include "BlinkTexture.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "imgui.h"
#include <unordered_map> 
#include "RockSolidNode.hpp" 

class RockSolidTextureManager
{
public:
    RockSolidTextureManager() = default;
    void loadTextures(const std::string& path, int size);
    void destroyTextures();
    std::unordered_map<int, BlinkTexture> textures;

    std::unordered_map<std::string, int> nameToType
    {
        {"gems", GEM_DEPOSIT},
        {"dirt", DIRT},
        {"metal", ROCK}
    };
};
