/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
 #pragma once

#include <vector>
#include <unordered_map>

#include "GemFallTextureManager.hpp"
#include "TextureGeneration.hpp"
#include "GridEntityBuilder.hpp"
#include "AnimationManager.hpp"

class GemFallGui
{
public:
    GemFallGui() = default;    // Constructor
    ~GemFallGui() = default;   // Destructor
    
    void init(const ImVec2& position, const ImVec2& size, int dim = 7);

    void addSpawn(const Coordinate&);
    void remove(const Coordinate&);
    void addGem(const Coordinate&);
    void permGem(const Coordinate&);

    Coordinate gridPosition(const ImVec2& pos) const;
    bool isInGui(const ImVec2& pos) const;

    void updateSDL();
    void updateVisuals(int);
    
    std::unordered_map<Coordinate, VisualEntity> visualEntityMap;
    std::unordered_map<Coordinate, VisualEntity*> gems;

    VisualEntity backgroundEntity;
    GridEntityBuilder builder;

    GemFallTextureManager tmana;
    AnimationManager am;

    BlinkTexture background;
    std::vector<BlinkTexture> squareTextures;

    bool previewMode = false;
    int frameSnap = 0;
};


