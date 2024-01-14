#include "GridImg.hpp"
#include "Application.hpp"
#include "RenderManager.hpp"
namespace blink2dgui
{
    GridImg::GridImg(const ImVec2& size, const ImVec2& pos, const BlinkTexture& texture) : size(size), position(pos), renderPosition(pos), texture(texture) {}

    void GridImg::render()
    {
        if (moveAction) {  moveAction(); }
        if (this->defaultAction) 
        {
            RenderManager::instance()->addRenderAction(texture, position.x, position.y, 1);
            //texture.render(position.x, position.y, nullptr, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    void GridImg::enableMovement(const ImVec2& sourcePosition, bool defaultAction)
    {
        if (Application::activeGameClock().getIntervalProgress() >= 1) this->start = true;
        this->defaultAction = defaultAction;        
        moveAction = [this, sourcePosition] 
        { 
            float factor = Application::activeGameClock().getIntervalProgress();
            if (factor >= 1)
            {
                if (this->start)
                {
                    factor = 0;
                    this->start = false;
                }
                else
                {
                    factor = 1;
                }
            }
            this->renderPosition = sourcePosition - (sourcePosition - this->position) * factor;
            RenderManager::instance()->addRenderAction(texture, renderPosition.x, renderPosition.y, 0);
            if (factor == 1)
            {
                this->moveAction = nullptr;
                this->setDefaultAction(true);
            }
        };
    }

    void GridImg::setDefaultAction(const bool& defaultAction)
    {
        this->defaultAction = defaultAction;
    }
        
}

