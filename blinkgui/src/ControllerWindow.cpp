#include "ControllerWindow.hpp"
#include "Application.hpp"

namespace blink2dgui
{
    ControllerWindow::ControllerWindow() 
    {
    }

    ControllerWindow::~ControllerWindow()
    {
    }


// This function should be placed in your application's rendering loop.
void ControllerWindow::renderWindow()
{
    ImGuiWindowFlags flags =  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    ImVec2 windowSize = ImVec2(1280, 40);  // Example size
    ImVec2 pos = ImVec2(0, 0);  // Example size
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(pos);
    // Begin a new ImGui window called "Control Window"
    ImGui::Begin("Control Window", nullptr, flags);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos() + ImVec2(600, 0); // To align our custom drawing with the window's position

    // We assume each icon is 20x20 pixels for this example. Adjust as needed.
    const float iconSize = 20.0f;
    float padding = 5.0f;  // Space between buttons

    // Draw "Back" button as a left-pointing triangle (play icon rotated 180 degrees)
    ImGui::InvisibleButton("back_btn", ImVec2(iconSize, iconSize));
    if (ImGui::IsItemClicked()) {
        // Handle Back button press here
        std::cout << "Back button pressed!" << std::endl;
    }
    if (ImGui::IsItemHovered())
    {
        draw_list->AddTriangleFilled(
            ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + padding),
            ImVec2(cursor_pos.x + padding, cursor_pos.y + iconSize / 2),
            ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + iconSize - padding),
            IM_COL32(100, 100, 255, 255)  // Lighter color if hovered
        );
    }
    else
    {
        draw_list->AddTriangleFilled(
            ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + padding),
            ImVec2(cursor_pos.x + padding, cursor_pos.y + iconSize / 2),
            ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + iconSize - padding),
            IM_COL32(255, 255, 255, 255)
        );
    }

   
    ImGui::SameLine();

    // Draw "Pause" button as two vertical rectangles
    cursor_pos = ImGui::GetCursorScreenPos() + ImVec2(600, 0);  // Update cursor position after SameLine
    ImGui::InvisibleButton("pause_btn", ImVec2(iconSize, iconSize));
    if (ImGui::IsItemClicked()) {
        // Handle Pause button press here
        std::cout << "Pause button pressed!" << std::endl;
    }
    draw_list->AddRectFilled(ImVec2(cursor_pos.x + padding, cursor_pos.y + padding), ImVec2(cursor_pos.x + padding * 3, cursor_pos.y + iconSize - padding), IM_COL32(255, 255, 255, 255));
    draw_list->AddRectFilled(ImVec2(cursor_pos.x + padding * 4, cursor_pos.y + padding), ImVec2(cursor_pos.x + padding * 6, cursor_pos.y + iconSize - padding), IM_COL32(255, 255, 255, 255));

    ImGui::SameLine();

    // Draw "Play" button as a right-pointing triangle
    cursor_pos = ImGui::GetCursorScreenPos() + ImVec2(600, 0);  // Update cursor position after SameLine
    ImGui::InvisibleButton("play_btn", ImVec2(iconSize, iconSize));
    if (ImGui::IsItemClicked()) {
        // Handle Play button press here
        std::cout << "Play button pressed!" << std::endl;
    }
    draw_list->AddTriangleFilled(
        ImVec2(cursor_pos.x + padding, cursor_pos.y + padding),
        ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + iconSize / 2),
        ImVec2(cursor_pos.x + padding, cursor_pos.y + iconSize - padding),
        IM_COL32(255, 255, 255, 255)
    );

    ImGui::SameLine();

    // Draw "Forward" button as a right-pointing double triangle or arrow
    cursor_pos = ImGui::GetCursorScreenPos() + ImVec2(600, 0);  // Update cursor position after SameLine
    ImGui::InvisibleButton("forward_btn", ImVec2(iconSize, iconSize));
    if (ImGui::IsItemClicked()) {
        // Handle Forward button press here
        std::cout << "Forward button pressed!" << std::endl;
    }
    draw_list->AddTriangleFilled(
        ImVec2(cursor_pos.x + padding, cursor_pos.y + padding),
        ImVec2(cursor_pos.x + iconSize / 2 - padding, cursor_pos.y + iconSize / 2),
        ImVec2(cursor_pos.x + padding, cursor_pos.y + iconSize - padding),
        IM_COL32(255, 255, 255, 255)
    );
    draw_list->AddTriangleFilled(
        ImVec2(cursor_pos.x + iconSize / 2, cursor_pos.y + padding),
        ImVec2(cursor_pos.x + iconSize - padding, cursor_pos.y + iconSize / 2),
        ImVec2(cursor_pos.x + iconSize / 2, cursor_pos.y + iconSize - padding),
        IM_COL32(255, 255, 255, 255)
    );

    // End the ImGui window
    ImGui::End();
}

}
