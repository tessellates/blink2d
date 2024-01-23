#include "GemFallTextureManager.hpp"
#include "BackgroundTexture.hpp"
#include "Application.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;


void GemFallTextureManager::loadTextures(const std::string& path, int size)
{
    if (gems.size() > 0)
    {
        return;
    }
    std::vector<std::pair<std::string, std::string>> fileNamesPaths;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                auto filePath = entry.path();
                if (fs::is_regular_file(filePath)) { // Making sure it's a file, not a directory
                    // You can use filePath.string() to get the full file path
                    // Or filePath.filename().string() to get just the file name
                    fileNamesPaths.push_back({filePath.filename().stem().string(), filePath.string()});

                    // For demonstration, let's just print the file name
                    std::cout << "Found file: " << filePath.filename().string() << std::endl;
                }
            }
        } else {
            std::cerr << "Directory does not exist or is not a directory: " << path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }

    auto renderer = blink2dgui::Application::instance()->getRenderer();
    for (const auto& [name,path] : fileNamesPaths)
    {
        std::cout << "key name : " << name << std::endl;
        std::cout << "key path : " << path << std::endl;
        auto texture = CreateTextureFromFile(renderer, path.c_str());
        int sheetWidth, sheetHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &sheetWidth, &sheetHeight);
        if (sheetWidth > sheetHeight)
        {
            auto textures = CutTextureSheet(renderer, texture);
            for (auto& tex : textures)
            {
                gems.push_back({tex, size, size});
            }
        }
        else
        {
            if (name == "extractor")
                spawner = {texture, size, size};
            if (name == "gempile2")
                pile = {texture, size, size};
        }
    }
}
