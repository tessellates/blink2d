/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "NoitaSimGui.hpp"
#include "Application.hpp"
#include "CellMeta.hpp"

void NoitaSimGui::init(int x, int y, int w, int h)
{
    frame.x = x;
    frame.y = y;
    frame.w = w;
    frame.h = h;
    mainTexture.initialize(blink2dgui::Application::instance()->getRenderer());
    mainTexture.scale = NoitaConfig::cellSize;
}

void NoitaSimGui::updateSDL()
{
    mainTexture.updateTexture();
    mainTexture.render(&frame);
}

void NoitaSimGui::updatePixelData(const std::array<int, NoitaConfig::width*NoitaConfig::height>& data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        mainTexture.pixels_[i] = colors[data[i] % colors.size()];
    }
}

void NoitaSimGui::updatePixelData(const std::array<Cell, NoitaConfig::numCells>& data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        mainTexture.pixels_[i] = colors[data[i].type + 21*data[i].variance];
    }
}

void NoitaSimGui::updatePixelData(const std::vector<SmartCell>& data)
{
    int counter = 0;
    for (int i = 0; i < data.size(); ++i)
    {
        mainTexture.pixels_[i] = colors[data[i].type % colors.size()];
        if (data[i].type)
        {
            counter++;
        }
    }
    particle_numbers.add(counter);
    if (particle_numbers.head == 59)
    {
        std::cout << "PARTICLES: " << particle_numbers.getAverage() << std::endl;
    }
}


Coordinate NoitaSimGui::gridLocation(int x, int y)
{
    return Coordinate((x - frame.x)/NoitaConfig::cellSize, (y - frame.y)/NoitaConfig::cellSize);
}

bool NoitaSimGui::inGrid(const Coordinate& coordinate)
{
    return coordinate.x >= 0 && coordinate.x <  (frame.w)/NoitaConfig::cellSize && coordinate.y >= frame.y && coordinate.y < (frame.h)/NoitaConfig::cellSize;
}