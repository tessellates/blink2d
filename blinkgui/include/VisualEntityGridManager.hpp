
#pragma once

#include "VisualEntity.hpp"

class VisualEntityGridManager
{
public:
    VisualEntityGridManager(int width, int height);    // Constructor
    VisualEntityGridManager(int width, int height, const ImVec2& windowSize, const ImVec2& windowPos);    // Constructor
    VisualEntityGridManager() = default;    // Constructor
    ~VisualEntityGridManager();   // Destructor

    void renderGrid();
    void renderSDL();

    ImVec2 absolutePosition(const Coordinate& pos) const;
    ImVec2 relativePosition(const Coordinate& pos) const;
    Coordinate gridPosition(const ImVec2& pos) const;

public:
    int width;           
    int height;  

    ImVec2 windowSize;
    ImVec2 windowPos;
    ImVec2 boardSize;

    ImVec2 squareSize;
    ImVec2 padding;
    
    ImGuiWindowFlags windowFlags;
    
    std::map<int, VisualEntity> visualEntityMap;
};
