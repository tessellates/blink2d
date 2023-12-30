#include "Transform.hpp"
#include "Application.hpp"

bool moveTowards(ImVec2& source, const ImVec2& target, float speed)
{
    float deltaTime = blink2dgui::Application::instance()->getGui().gameClock.getProgress();
    float distanceToMove = speed * deltaTime;

    // Calculate the distance to the target
    ImVec2 toTarget = {target.x - source.x, target.y - source.y};
    float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    // Check if we are close enough to consider it as reaching the target
    if (distance < distanceToMove || distance == 0.0f) {
        source = target;
        return false;
    } else {
        source = lerp(source, target, distanceToMove / distance);
    }
    return true;
}

void moveVec(const ImVec2& source, const ImVec2& target, ImVec2& currentShift, float speed) 
{
    float deltaTime = blink2dgui::Application::instance()->getGui().gameClock.getProgress();
    float distanceToMove = speed * deltaTime;

    // Calculate the distance to the target
    ImVec2 toTarget = {target.x - source.x, target.y - source.y};
    float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
    if (distance < distanceToMove || distance == 0.0f) 
    {
        currentShift = toTarget;
    }
    else
    {
        currentShift += lerpVec(source, target, distanceToMove / distance);
        float distanceShift = std::sqrt(currentShift.x * currentShift.x + currentShift.y * currentShift.y);
        if (distanceShift > distance)
        {
            currentShift = toTarget;
        }
    }
}