#include "scenes/MainMenuScene.hpp"

#include "raylib.h"
#include "ui/UiHelper.hpp"

namespace calculissimo::scenes {


Color selectedColor(bool selected) {
    return selected ? DARKBLUE : GRAY;
}

/// Dessine le menu principal
MainMenuAction drawMainMenuScene(const int screenWidth, const int screenHeight, game::Difficulty& selectedDifficulty, game::GameMode& selectedMode) {
    DrawText("Calculissimo", 30, 20, 34, DARKBLUE);
    DrawText("Choisis ta difficulté et ton mode", 30, 65, 20, GRAY);

    constexpr int buttonWidth = 170;
    constexpr int buttonHeight = 40;

    constexpr int difficultyY = 130;
    DrawText("Difficulté", 30, difficultyY - 30, 22, DARKGRAY);

    if (ui::drawButton(30, difficultyY, buttonWidth, buttonHeight, "Facile", selectedColor(selectedDifficulty == game::Difficulty::Easy), WHITE)) {
        selectedDifficulty = game::Difficulty::Easy;
    }
    if (ui::drawButton(30 + buttonWidth + 15, difficultyY, buttonWidth, buttonHeight, "Moyen", selectedColor(selectedDifficulty == game::Difficulty::Medium), WHITE)) {
        selectedDifficulty = game::Difficulty::Medium;
    }
    if (ui::drawButton(30 + (buttonWidth + 15) * 2, difficultyY, buttonWidth, buttonHeight, "Difficile", selectedColor(selectedDifficulty == game::Difficulty::Hard), WHITE)) {
        selectedDifficulty = game::Difficulty::Hard;
    }

    constexpr int modeY = difficultyY + buttonHeight + 40;
    DrawText("Mode", 30, modeY - 30, 22, DARKGRAY);

    if (ui::drawButton(30, modeY, buttonWidth, buttonHeight, "Chrono", selectedColor(selectedMode == game::GameMode::Chrono), WHITE)) {
        selectedMode = game::GameMode::Chrono;
    }
    if (ui::drawButton(30 + buttonWidth + 15, modeY, buttonWidth, buttonHeight, "Entrainement", selectedColor(selectedMode == game::GameMode::Entrainement), WHITE)) {
        selectedMode = game::GameMode::Entrainement;
    }

    MainMenuAction action;

    constexpr int actionY = modeY + buttonHeight + 55;
    if (ui::drawButton(30, actionY, 200, 45, "Jouer", DARKGREEN, WHITE)) {
        action.startGame = true;
    }

    if (ui::drawButton(30 + 220, actionY, 200, 45, "Boutique", MAROON, WHITE)) {
        action.openShop = true;
    }

    DrawText("[ESC] quitter", 30, screenHeight - 40, 20, GRAY);

    return action;
}

}

