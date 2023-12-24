#include "BlinkTexture.hpp"
#include "Application.hpp"

BlinkTexture::BlinkTexture(SDL_Renderer* renderer, SDL_Texture* texture)
    : m_renderer(renderer), m_texture(texture) {
    // Optionally, get the width and height of the texture
    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
}

BlinkTexture::BlinkTexture(SDL_Texture* texture) : BlinkTexture(blink2dgui::Application::instance()->getRenderer(), texture)
{
    // Optionally, get the width and height of the texture
    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
}


BlinkTexture::~BlinkTexture() {
    if (m_texture) {
        //SDL_DestroyTexture(m_texture);
    }
}

void BlinkTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const {
    SDL_SetRenderTarget(m_renderer, NULL);    

    SDL_Rect renderQuad = { x, y, m_width, m_height };

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(m_renderer, m_texture, clip, &renderQuad, angle, center, flip);
}