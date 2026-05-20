#pragma once

#include "game/Difficulty.hpp"
#include "game/GameMode.hpp"

namespace calculissimo::scenes {

    struct MainMenuAction {
        bool startGame = false;
        bool openShop = false;
    };

    MainMenuAction drawMainMenuScene(int screenWidth, int screenHeight, game::Difficulty& selectedDifficulty, game::GameMode& selectedMode);
}

