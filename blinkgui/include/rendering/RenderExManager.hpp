#pragma once

#include "Singleton.hpp"
#include "rendering/RenderAction.hpp"

#include <deque>

class RenderExManager : public Singleton<RenderExManager>
{
    friend class Singleton<RenderExManager>; // Grant base access to constructor.
public:
    // boiler-plate singleton
    RenderExManager(const RenderExManager&) = delete;
    void operator=(const RenderExManager&) = delete;

    void renderSDL();
    RenderAction& newRenderAction(int = 0);

private:
    RenderExManager() = default;
    ~RenderExManager() = default;   

    std::deque<RenderAction> baseLayer;
    std::array<std::deque<RenderAction>, 10> layers;
};
