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
#include <map>

#include "ConnectModel.hpp"
#include "GameState.hpp"
#include "GameClock.hpp"
#include "BackgroundTexture.hpp"
#include "GameGui.hpp"
#include "VisualEntity.hpp"

#include "RenderAction.hpp"
#include "GridEntityBuilder.hpp"
#include "RockSolidTextureManager.hpp"
#include "RockSolidModel.hpp"

namespace blink2dgui
{
    class RockSolidGui
    {
    public:
        RockSolidGui();    // Constructor
        ~RockSolidGui();   // Destructor


    private:
        std::map<int, VisualEntity> visualEntityMap;
        GridEntityBuilder builder;
        RockSolidTextureManager manager;
    };
}

