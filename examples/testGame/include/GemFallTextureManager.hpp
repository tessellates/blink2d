#pragma once

#include "Application.hpp"
#include "BlinkTexture.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "imgui.h"
#include <unordered_map> 

class GemFallTextureManager
{
public:
    GemFallTextureManager() = default;
    void loadTextures(const std::string& path, int size);
    void destroyTextures();

    BlinkTexture spawner;
    BlinkTexture pile;
    std::vector<BlinkTexture> gems;
};
