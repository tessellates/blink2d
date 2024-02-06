#include "NoitaControlPanel.hpp"
#include "CellManager.hpp"

NoitaControlPanel::NoitaControlPanel(const ImVec2& initWindowSize, const ImVec2& initWindowPos)
    : windowSize(initWindowSize), windowPos(initWindowPos) {
    windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar |
                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                  ImGuiWindowFlags_NoCollapse;
}

void NoitaControlPanel::render(CellManager& cm, int& brushSize) {
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowPos);
    ImGui::Begin("Noita Control Panel", nullptr, windowFlags);

    // Add your control elements here
    //ImGui::InputFloat("Gravity", &state.gravity);
    //ImGui::InputFloat("Drag Coefficient", &state.dragCoefficient);
    ImGui::InputInt("Brush size", &brushSize);

    if (ImGui::Button("#Test Spawn")) {
        cm.testSpawn();  // This function is called when the button is pressed
    }

    // Add a button for test spawn
    if (ImGui::Button("#Random Test Spawn")) {
        cm.randomTestSpawn();  // This function is called when the button is pressed
    }
/*
        // Add a button for test spawn
    if (ImGui::Button("#spawn2")) {
        cp.testSpawn2();  // This function is called when the button is pressed
    }*/
    
    
    // Add a button for test spawn
    /*
    int value = cp.speed;
    int shift = 0;
    while (value > 0)
    {
        shift++;
        value >>= 3;
    }
    ImGui::Text("Value: %d", shift);

    // "+" button for left bit shift
    if (ImGui::Button("+")) {
        cp.speed <<= 3; // Perform left bit shift
        cp.speed += 5;
    }

    // "-" button for right bit shift
    if (ImGui::Button("-")) {
        cp.speed >>= 3; // Perform right bit shift
    }*/
    
    ImGui::Text("Speed: %d", cm.walk.speed);

    if (ImGui::Button("+")) {
        cm.walk.speed++;

    }

    // "-" button for right bit shift
    if (ImGui::Button("-")) {
        if (cm.walk.speed > 0)
        {
            cm.walk.speed--;
        }
    }

 // Direction buttons
    ImGui::InputInt("pattern:", &cm.walk.direction);

    // Display the current direction
    ImGui::Text("Current pattern: %d", cm.walk.direction);

    // Checkbox for 'phasing'
    ImGui::Checkbox("parallel", &cm.move.parallel);
    if (cm.move.parallel) {
        ImGui::Text("parallel is ON");
    } else {
        ImGui::Text("parallel is OFF");
    }
/*
    // Checkbox for 'phasing'
    ImGui::Checkbox("Phasing", &cp.phasing);
    if (cp.phasing) {
        ImGui::Text("Phasing is ON");
    } else {
        ImGui::Text("Phasing is OFF");
    }

    if (!cp.phasing)
    {
        if (ImGui::Button("Increase Phase")) {
            if (cp.phase < 3)
                cp.phase++;
        }
        ImGui::SameLine();
        if (ImGui::Button("Decrease Phase")) {
            if (cp.phase > 0)
                cp.phase--;
        }
        ImGui::Text("Current Phase: %d", cp.phase);
    }
 */

    ImGui::End();
}
