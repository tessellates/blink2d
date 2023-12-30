#pragma once

#include "Singleton.hpp"
#include "rendering/RenderAction.hpp"

#include <deque>

class RenderManager : public Singleton<RenderManager>
{
    friend class Singleton<RenderManager>; // Grant base access to constructor.
public:
    // boiler-plate singleton
    RenderManager(const RenderManager&) = delete;
    void operator=(const RenderManager&) = delete;

    void renderSDL();
    void addRenderAction(const BlinkTexture& texture, int x, int y, int layerID);
    void addRenderAction(const Transform& transform, const BlinkTexture& texture, int layerID);

private:
    RenderManager() = default;
    ~RenderManager() = default;   

    std::array<std::deque<RenderAction>, 10> layers;
};
