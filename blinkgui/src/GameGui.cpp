/**
 * Copyright (C) ZdefaultCompanyZ - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "GameGui.hpp"

namespace blink2dgui {

GameGui::GameGui() {
    int model = 0;
    squareGui_ = SquareGui();
    // Initialization code for GameGui (if any)
}

GameGui::~GameGui() {
    // Cleanup code for GameGui (if any)
}

void GameGui::render() {
    squareGui_.renderGrid();

    // Additional rendering code for GameGui (if any)
}

}  // namespace blink2dgui
