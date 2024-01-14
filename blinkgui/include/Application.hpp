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

#include "GameGui.hpp"
#include "SettingsPanel.hpp"
#include "ControllerWindow.hpp"
#include "Singleton.hpp"
#include "BlinkGame.hpp"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

class SideGui;

namespace blink2dgui
{
    /**
    * @class Application
    * @brief Init the application    
    */
    class Application : public Singleton<Application>
    {
        friend class Singleton<Application>; // Grant base access to constructor.

        public:
            // boiler-plate singleton
            Application(Application &other) = delete; 
            void operator=(const Application &) = delete;

            void loop();
            void init(int option = 0);
            bool isRunning();
            SDL_Renderer* getRenderer() const;

            int WIDTH = 1280;
            int HEIGHT = 800;

            int WIDTH_DEFAULT = 1280;
            int HEIGHT_DEFAULT = 800;

            float HEIGHT_MOD = 1;
            
            
            static GameClock& activeGameClock();
            static BlinkGame* activeGame();

        private:
            Application();
            ~Application();   

            SDL_Event event_;
            SDL_Window* window_;
            SDL_Renderer* renderer_;
            ImGuiIO* io_;
            ImVec4 clear_color_;

            bool done_ = false;
            
            SettingsPanel panel_;
            ControllerWindow controllerWindow_;
            BlinkGame* game;
    };
}
