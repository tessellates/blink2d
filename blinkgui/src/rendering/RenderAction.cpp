
#include "rendering/RenderManager.hpp"

template<typename T>
T* getOptionalPtr(std::optional<T>& opt) {
    return opt.has_value() ? &*opt : nullptr;
}

RenderAction::RenderAction(int x, int y, const BlinkTexture& texture) : x(x), y(y), texture(texture)
{

}

RenderAction::RenderAction(int x, int y, const BlinkTexture& texture, double angle, const SDL_Point& center, const SDL_RendererFlip& flip) : x(x), y(y), texture(texture), angle(angle), center(center), flip(flip)
{

}

void RenderAction::render()
{
    texture.render(x, y, getOptionalPtr(clip), angle, getOptionalPtr(center), flip);
}