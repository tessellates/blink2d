#pragma once

#include "RockSolidNode.hpp"

enum ToolType
{
    DEMOLITION,
    PLACE_NODE
};

class Tool
{
public: 
    Tool(ToolType toolType, RockSolidNodeType nodeType);
    Tool(ToolType toolType);
    
    ToolType toolType;
    std::optional<RockSolidNodeType> nodeType;    
};
