#include "BackgroundTexture.hpp"
#include "TextureVector.hpp"

inline TextureVector CreateBackgroundTexture(float size)
{
    TextureVector vector = TextureVector();
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0.5f, 0, 0, 1), size, size));
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0, 0.5f, 0, 1), size, size));
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0.5f, 0.5f, 0, 1), size, size));
    return vector;
}