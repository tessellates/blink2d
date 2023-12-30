#pragma once

#include "Transform.hpp"

class IRenderStrategy
{
    virtual ~IRenderStrategy() = default;
    virtual void render(const Transform& transform) = 0;
};
 