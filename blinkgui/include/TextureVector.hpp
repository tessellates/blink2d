/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <vector>
#include "Shape.hpp"
#include "GridEntity.hpp"
#include <SDL.h>
#include <SDL_image.h>

namespace blink2dgui
{
    class TextureVector {
    public:

        destroy() 
        {
            for (SDL_Texture* texture : textures) 
            {
                if (texture) {
                    SDL_DestroyTexture(texture);
                }
            }   
        }

        void addTexture(SDL_Texture* texture) {
            textures.push_back(texture);
        }

        SDL_Texture* operator[](size_t index) {
            return textures[index];
        }

        const SDL_Texture* operator[](size_t index) const {
            return textures[index];
        }

    private:
        std::vector<SDL_Texture*> textures;
    };
}

