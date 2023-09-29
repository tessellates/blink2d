#include <iostream>
#include <Application.hpp>
#include <HexGui.hpp>
#include <cmath>

namespace blink2dgui
{
    Application *Application::GetInstance()
    {
        /**
         * This is a safer way to create an instance. instance = new Singleton is
         * dangerous in case two instance threads wants to access at the same time
         */
        if(singleton_ == nullptr)
        {
            singleton_ = new Application();
        }
        return singleton_;
    }

    void Application::Destroy(Application& app)
    {
        delete &app;
        singleton_ = nullptr;
    }

    Application::Application()
    {
        // Setup SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
        }

        // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        // Create window with SDL_Renderer graphics context
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
        window_ = SDL_CreateWindow("BLINK 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, window_flags);
        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer_ == nullptr)
        {
            SDL_Log("Error creating SDL_Renderer!");
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io_ = &ImGui::GetIO();
        io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io_->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
        ImGui_ImplSDLRenderer2_Init(renderer_);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);

        clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        gui_ = HexGui();
        sgui_ = SquareGui();
        shaper_ = ShapeSelector();
    }

    Application::~Application()
    {
        // Cleanup
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void Application::loop()
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        while (SDL_PollEvent(&event_))
        {
            ImGui_ImplSDL2_ProcessEvent(&event_);
            if (event_.type == SDL_QUIT)
                done_ = true;
            if (event_.type == SDL_WINDOWEVENT && event_.window.event == SDL_WINDOWEVENT_CLOSE && event_.window.windowID == SDL_GetWindowID(window_))
                done_ = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        shaper_.renderWindow();
        if (shaper_.isSquareSelected())
        {
            sgui_.renderGrid();
        }
        if (shaper_.isHexagonSelected())
        {
            gui_.renderGrid();
        }
        //testGui();

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(renderer_, io_->DisplayFramebufferScale.x, io_->DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer_, (Uint8)(clear_color_.x * 255), (Uint8)(clear_color_.y * 255), (Uint8)(clear_color_.z * 255), (Uint8)(clear_color_.w * 255));
        SDL_RenderClear(renderer_);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer_);
    }

    void Application::testGui()
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (demo_)
            ImGui::ShowDemoWindow(&demo_);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &demo_);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &other_);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color_); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io_->Framerate, io_->Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (other_)
        {
            ImGui::Begin("Another Window", &other_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                other_ = false;
            ImGui::End();
        }
    }

    bool Application::isRunning()
    {
        return !done_;
    }

    Application* Application::singleton_ = nullptr;
}