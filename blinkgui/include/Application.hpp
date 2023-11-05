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

#include <GameGui.hpp>
#include <ShapeSelector.hpp>
#include <ControllerWindow.hpp>
#include <Singleton.hpp>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

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
            void changeGameSpeed(int gameSpeed);
            SDL_Renderer* getRenderer() const;
            GameGui& getGui() const;

            int WIDTH = 1280;
            int HEIGHT = 800;
            GameGui* gui_ = nullptr;

        private:
            Application();
            ~Application();   

            SDL_Event event_;
            SDL_Window* window_;
            SDL_Renderer* renderer_;
            ImGuiIO* io_;
            ImVec4 clear_color_;

            bool done_ = false;
            
            ShapeSelector shapeSelector_;
            ControllerWindow controllerWindow_;
    };
}