#include <SDL.h>
#include <imgui.h>
#include <map>
#include "BackgroundTexture.hpp"

class ColorTextureManager 
{
public:
    ColorTextureManager() = default;
    ColorTextureManager(SDL_Renderer* renderer, int width, int height);
    SDL_Texture* GetTexture(const ImVec4& color);

private:
    SDL_Renderer* renderer_;
    int textureWidth_;
    int textureHeight_;
    //std::map<ImVec4, SDL_Texture*> textureMap_;

    SDL_Texture* CreateTexture(const ImVec4& color);
};
