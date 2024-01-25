
#include "NoitaSimGame.hpp"
#include "Application.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time


std::array<Uint32, 20> convertColorsToUint32(const std::array<ImVec4, 20>& colors) {
    std::array<Uint32, 20> uint32Colors;

    for (size_t i = 0; i < colors.size(); ++i) {
        const auto& col = colors[i];
        Uint8 r = static_cast<Uint8>(col.x * 255);
        Uint8 g = static_cast<Uint8>(col.y * 255);
        Uint8 b = static_cast<Uint8>(col.z * 255);
        Uint8 a = static_cast<Uint8>(col.w * 255);

        uint32Colors[i] = (r << 24) | (g << 16) | (b << 8) | a;
    }

    return uint32Colors;
}

void NoitaSimGame::init(const GameParameters& parameters)
{
    windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    padding = ImVec2(0, 0);
    this->parameters = parameters;
    ImVec2 guiSpace = parameters.gameSpace - padding * 2;
    ImVec2 guiLocation = parameters.gameRoot + padding;

    fastTexture.initialize(blink2dgui::Application::instance()->getRenderer());

    // Define an array of 20 hardcoded random colors
    std::array<ImVec4, 20> colors = {
        ImVec4(0.0832, 0.1560, 0.9222, 1.0),
        ImVec4(0.1006, 0.5563, 0.8696, 1.0),
        ImVec4(0.4417, 0.1276, 0.5991, 1.0),
        ImVec4(0.6180, 0.5614, 0.7865, 1.0),
        ImVec4(0.1581, 0.9560, 0.5877, 1.0),
        ImVec4(0.7747, 0.1965, 0.5372, 1.0),
        ImVec4(0.5284, 0.1262, 0.0339, 1.0),
        ImVec4(0.7606, 0.7810, 0.0025, 1.0),
        ImVec4(0.4269, 0.8886, 0.3616, 1.0),
        ImVec4(0.0748, 0.2032, 0.0005, 1.0),
        ImVec4(0.8029, 0.9388, 0.2829, 1.0),
        ImVec4(0.0918, 0.9876, 0.8837, 1.0),
        ImVec4(0.8101, 0.4227, 0.4114, 1.0),
        ImVec4(0.5919, 0.2103, 0.5006, 1.0),
        ImVec4(0.6364, 0.0818, 0.3202, 1.0),
        ImVec4(0.0340, 0.2054, 0.9683, 1.0),
        ImVec4(0.8368, 0.3891, 0.7698, 1.0),
        ImVec4(0.3394, 0.7454, 0.7083, 1.0),
        ImVec4(0.1088, 0.3799, 0.5746, 1.0),
        ImVec4(0.3240, 0.8830, 0.2737, 1.0)
    };
    sdl_colors = convertColorsToUint32(colors);
}

void NoitaSimGame::clicked(const ImVec2& position, int id)
{

}

void NoitaSimGame::hover(const ImVec2& position, int id)
{

}

void NoitaSimGame::renderImGui()
{
    ImGui::SetNextWindowSize(parameters.gameSpace);
    ImGui::SetNextWindowPos(parameters.gameRoot);

    ImGuiStyle originalStyle = ImGui::GetStyle();

    // Modify the style for a specific window
    ImGui::GetStyle().WindowPadding = ImVec2(0.0f, 0.0f);

    ImGui::Begin("NoitaSim Game", nullptr, windowFlags);

    ImGui::End();
    ImGui::GetStyle() = originalStyle;
}

void NoitaSimGame::updateSDL()
{
    clock.update();
    updateGame();


    //NoitaSimGui.updateSDL();
    //renderManager.renderSDL();
    fastTexture.updateTexture();
    fastTexture.render(parameters.gameRoot.x, parameters.gameRoot.y);
}

void NoitaSimGame::updateGame()
{
    //srand(static_cast<unsigned int>(time(nullptr)));
    for(auto& pixel : fastTexture.pixels_)
    {
        int randomIndex = (rand() % sdl_colors.size());
        pixel = sdl_colors[randomIndex];
        /*
        int randomIndex = rand() % textures.size();
        ex.texture = textures[randomIndex];
        if (randomIndex == 2 || randomIndex == 4 || randomIndex == 6)
        {
            ex.texture = textures[randomIndex];
            ex.inUse = true;
        }
        else
        {
            ex.inUse = false;
            ex.texture = nullptr;
        }*/
        //ex.inUse = randomIndex == 2 || randomIndex == 4 || randomIndex == 6;
    }
}

void NoitaSimGame::forward()
{
   //NoitaSimModel.forward();
}

void NoitaSimGame::backward()
{
    //NoitaSimModel.backward();
}
   