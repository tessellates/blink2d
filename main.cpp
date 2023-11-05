#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <Application.hpp>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

// Main code
int main(int, char**)
{
    blink2dgui::Application& app = *blink2dgui::Application::instance();
    app.init();
    while (app.isRunning())
    {
        app.loop();
    }
    blink2dgui::Application::destroyInstance();
    return 0;
}
