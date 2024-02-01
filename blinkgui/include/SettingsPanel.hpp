/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <vector>
#include <optional>
#include <array>

#include "GameSettings.hpp"
#include "CircularBuffer.hpp"

namespace blink2dgui
{
    class SettingsPanel
    {
    public:
        SettingsPanel();   // Constructor
        ~SettingsPanel() = default;   // Destructor

        // Render the shape selector window
        void renderWindow(float scale = 1);
        void enableSettings(const GameSettings& settings);

    private:
        int selectedItem;
        int gameSpeed;
        int gridSize;
        std::optional<GameSettings> settings;
        CircularBuffer<float,30> fpsBuffer;
    };
}

