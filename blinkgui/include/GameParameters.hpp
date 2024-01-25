#pragma once

#include "imgui.h"

struct GameParameters
{
    ImVec2 gameRoot;
    ImVec2 gameSpace;
};

inline GameParameters connectParameters(float scale = 1)
{
    return {ImVec2(280, 40)*scale, ImVec2(680, 680)*scale};
}

inline GameParameters NoitaParameters(float scale = 1)
{
    return {ImVec2(280,0)*scale, ImVec2(1000, 720)*scale};
}
