
#include "RenderAction.hpp"
#include "Utility.hpp"

RenderAction::RenderAction(int x, int y, const BlinkTexture& texture) : x(x), y(y), texture(texture)
{

}

RenderAction::RenderAction(int x, int y, const BlinkTexture& texture, double angle, const SDL_Point& center, const SDL_RendererFlip& flip) : x(x), y(y), texture(texture), angle(angle), center(center), flip(flip)
{

}

RenderAction::RenderAction(const Transform& transform, const BlinkTexture& texture) : x(transform.position.x), y(transform.position.y), texture(texture), angle(transform.rotation), flip(transform.flip)
{

}


void RenderAction::render()
{
    texture.render(x, y, getOptionalPtr(clip), angle, getOptionalPtr(center), flip);
}