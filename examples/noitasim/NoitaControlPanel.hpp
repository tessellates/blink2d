// NoitaControlPanel.hpp
#pragma once

#include "imgui.h"
#include <array>

// Forward declaration
class CellManager;

class NoitaControlPanel {
public:
    NoitaControlPanel() = default;
    NoitaControlPanel(const ImVec2& initWindowSize, const ImVec2& initWindowPos);
    void render(CellManager&, int&);

private:
    ImVec2 windowSize;
    ImVec2 windowPos;
    ImGuiWindowFlags windowFlags;
};
