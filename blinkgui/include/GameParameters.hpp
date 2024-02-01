#pragma once

#include "imgui.h"

struct GameParameters
{
    ImVec2 gameRoot;
    ImVec2 gameSpace;
    ImVec2 panelRoot;
    ImVec2 panelSpace;
};

inline GameParameters connectParameters(float scale = 1)
{
    return {ImVec2(280, 40)*scale, ImVec2(680, 680)*scale};
}

inline GameParameters NoitaParameters(float scale = 1)
{
    return {ImVec2(280,0)*scale, ImVec2(1000, 720)*scale, ImVec2(0, 400)*scale, ImVec2(280,320)*scale};
}
