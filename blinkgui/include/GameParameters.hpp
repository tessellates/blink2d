#pragma once

#include "imgui.h"

struct GameParameters
{
    ImVec2 gameRoot;
    ImVec2 gameSpace;
};

inline GameParameters connectParameters(float scale = 1)
{
    return {ImVec2(280, 40)*scale, ImVec2(720, 720)*scale};
}