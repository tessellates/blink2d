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


#include <HexGui.hpp>
#include <SquareGui.hpp>
#include <ShapeSelector.hpp>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace blink2dgui
{
    /**
    * @class Application
    * @brief Init the application    
    */
    class Application
    {
        public:
            /**
             * This is the static method that controls the access to the singleton
             * instance. On the first run, it creates a singleton object and places it
             * into the static field. On subsequent runs, it returns the client existing
             * object stored in the static field.
             */
            static Application *GetInstance();
            static void Destroy(Application& app);
            Application(Application &other) = delete; 

            /**
             * Singletons should not be assignable.
             */
            void operator=(const Application &) = delete;

            void loop();
            void testGui();
            void hexGui();
            bool isRunning();

        private:
            static Application* singleton_; 
            Application();
            ~Application();   

            SDL_Event event_;
            SDL_Window* window_;
            SDL_Renderer* renderer_;
            ImGuiIO* io_;
            ImVec4 clear_color_;

            bool demo_ = true;
            bool other_ = false;
            bool done_ = false;
            HexGui gui_;
            SquareGui sgui_;
            ShapeSelector shaper_;
    };
}