#include "BackgroundTexture.hpp"
#include "TextureVector.hpp"
#include "Application.hpp"
#include "rendering/BlinkTexture.hpp"

namespace blink2dgui
{
inline std::vector<BlinkTexture> createConnectTextureVector(float size)
{
    std::vector<BlinkTexture> vector;
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0.5f, 0, 0, 1), size, size));
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0, 0.5f, 0, 1), size, size));
    vector.push_back(CreateColorTexture(Application::instance()->getRenderer(), ImVec4(0.5f, 0.5f, 0, 1), size, size));
    return vector;
}
}
