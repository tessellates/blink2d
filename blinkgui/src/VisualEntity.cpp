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

    clean();
}

void VisualEntity::clean()
{
    auto newEnd = std::remove_if(renderInstructions.begin(), renderInstructions.end(), 
                                 [](const RenderInstruction& ri) { return ri.isDead(); });
    renderInstructions.erase(newEnd, renderInstructions.end());
}