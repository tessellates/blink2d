/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include <vector>
#include <unordered_map>

#include "TextureGeneration.hpp"
#include "GridEntityBuilder.hpp"

class ConnectGui
{
public:
    ConnectGui() = default;    // Constructor
    ~ConnectGui() = default;   // Destructor
    
    void init(const ImVec2& position, const ImVec2& size);
    void addConnectEntity(const Coordinate& postion, int color);
    void removeConnectEntity(const Coordinate& postion);
    void changeConnectEntity(const Coordinate& postion, int color);

    Coordinate gridPosition(const ImVec2& pos) const;
    bool isInGui(const ImVec2& pos) const;

    void updateSDL();
    
    std::unordered_map<Coordinate, VisualEntity> visualEntityMap;
    VisualEntity backgroundEntity;
    GridEntityBuilder builder;

    BlinkTexture background;
    std::vector<BlinkTexture> squareTextures;

    bool previewMode = false;
};


