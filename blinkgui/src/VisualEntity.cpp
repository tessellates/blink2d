#include "VisualEntity.hpp"

void VisualEntity::render()
{
    if (ms)
    {
        if(!(*ms).update(transform))
            ms.reset();

    }
    /*
    for (auto& ms : moveStrategies)
    {
        ms.update(transform);
    }*/
    for (auto& ri : renderInstructions)
    {
        ri.render(transform);
    }
}