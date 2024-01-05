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
#include "GridEntity.hpp"
#include <SDL.h>
#include <SDL_image.h>

namespace blink2dgui
{
    class TextureVector {
    public:
        // Type definitions for the iterator and const_iterator
        using iterator = std::vector<SDL_Texture*>::iterator;
        using const_iterator = std::vector<SDL_Texture*>::const_iterator;

        void destroy() 
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

        // Method to get the beginning iterator
        iterator begin() {
            return textures.begin();
        }

        // Method to get the beginning const_iterator
        const_iterator begin() const {
            return textures.begin();
        }

        // Method to get the end iterator
        iterator end() {
            return textures.end();
        }

        // Method to get the end const_iterator
        const_iterator end() const {
            return textures.end();
        }

    private:
        std::vector<SDL_Texture*> textures;
    };
}

