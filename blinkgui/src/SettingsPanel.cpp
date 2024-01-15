#include "SettingsPanel.hpp"
#include "Application.hpp"

namespace blink2dgui
{
    void SettingsPanel::renderWindow(float scale)
    {
        ImGuiWindowFlags flags =  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
        ImVec2 windowSize = ImVec2(280, 720)*scale;  // Example size
        ImVec2 pos = ImVec2(0, 40)*scale;  // Example size
        ImVec2 pos2 = ImVec2(1000, 40)*scale;  // Example size
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(pos);

        ImGui::Begin("Game Settings", nullptr, flags);

        const char* items[] = { "None", "Snake", "Connect", "Rocksolid" };
        ImGui::Combo("Game", &selectedItem, items, IM_ARRAYSIZE(items));

        ImGui::Spacing();

        // Confirm button
        if (ImGui::Button("Confirm##game")) {
            Application::instance()->init(selectedItem);
        }

        if (!settings)
        {
            ImGui::End();
            return;
        }

        if(settings->freeSpeed)
        {
            if(ImGui::SliderInt("Game Speed", &gameSpeed, 25, 1000))
            {
                Application::instance()->activeGameClock().setGameSpeed(gameSpeed);
            }
        }

        if(settings->freeGrid)
        {
            // Create a slider from 5 to 300
            ImGui::SliderInt("Grid Size", &gridSize, 4, 40);

            // Add some spacing
            ImGui::Spacing();

            // Confirm button
            if (ImGui::Button("Confirm##grid")) {

            }
        }

        //if (Application::instance()->gui_)
        //    ImGui::Text("FPS: %.3f", 1.0f / Application::instance()->getGui().gameClock.getDeltaTime() * 1000);

        ImGui::End();

    }
    void SettingsPanel::enableSettings(const GameSettings& settings)
    {
        this->settings = settings;
        //gameSpeed = Application::activeGameClock().getGameSpeed();
    }
}

