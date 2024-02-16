/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include <vector>
#include <unordered_map>

#include "Coordinate.hpp"
#include "FastTexture.hpp"
#include "NoitaConfig.hpp"
#include "CellMeta.hpp"
#include "CircularBuffer.hpp"

class NoitaSimGui
{
public:
    NoitaSimGui() = default;    // Constructor
    ~NoitaSimGui() = default;   // Destructor
    void updateSDL();
    void updatePixelData(const std::array<SmartCell, NoitaConfig::numCells>&);
    void init(int, int, int, int);
    Coordinate gridLocation(int, int);
    bool inGrid(const Coordinate&);

    FastTexture mainTexture;
    std::array<Uint32, 42> colors = {
        0x00000000,
        0xFFFF00FF, // Yellow
        0x00FF00FF, // Green
        0x0000FFFF, // Blue
        0xFF0000FF, // Red
        0xFF00FFFF, // Magenta
        0x00FFFFFF, // Cyan
        0xFFFFFFFF, // White
        0x000000FF, // Black
        0x808080FF, // Gray
        0x800000FF, // Maroon
        0x008000FF, // Dark Green
        0x808000FF, // Olive
        0x000080FF, // Navy
        0x800080FF, // Purple
        0x008080FF, // Teal
        0xFFA500FF, // Orange
        0xA52A2AFF, // Brown
        0x8A2BE2FF, // Blue Violet
        0xDEB887FF, // BurlyWood
        0x5F9EA0FF,  // CadetBlue
        // VARIANCE
        0x00000000,         // Transparent
        0xF0E68CFF,         // Khaki (instead of Yellow)
        0x32CD32FF,         // LimeGreen (instead of Green)
        0x1E90FFFF,         // DodgerBlue (instead of Blue)
        0xDC143CFF,         // Crimson (instead of Red)
        0xFF1493FF,         // DeepPink (instead of Magenta)
        0x20B2AAFF,         // LightSeaGreen (instead of Cyan)
        0xFFF8DCFF,         // Cornsilk (instead of White)
        0x696969FF,         // DimGray (instead of Black)
        0xC0C0C0FF,         // Silver (instead of Gray)
        0xB22222FF,         // Firebrick (instead of Maroon)
        0x228B22FF,         // ForestGreen (instead of Dark Green)
        0xF4A460FF,         // SandyBrown (instead of Olive)
        0x4682B4FF,         // SteelBlue (instead of Navy)
        0x9400D3FF,         // DarkViolet (instead of Purple)
        0x40E0D0FF,         // Turquoise (instead of Teal)
        0xFF4500FF,         // OrangeRed (instead of Orange)
        0xD2691EFF,         // Chocolate (instead of Brown)
        0x9932CCFF,         // DarkOrchid (instead of Blue Violet)
        0xFFD700FF,         // Gold (instead of BurlyWood)
        0x00CED1FF          // DarkTurquoise (instead of CadetBlue)
    };
    SDL_Rect frame;
    CircularBuffer<float,60> particle_numbers;
};


