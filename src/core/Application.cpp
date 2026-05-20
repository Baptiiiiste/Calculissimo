#include "core/Application.hpp"

#include "raylib.h"
#include "scenes/GameScene.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/ShopScene.hpp"

namespace calculissimo::core {

int Application::run() {
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Calculissimo");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    int shopScrollOffset = 0;
    bool shouldExit = false;

    while (!WindowShouldClose() && !shouldExit) {
        if (currentScene == Scene::MainMenu) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            const auto action = scenes::drawMainMenuScene(screenWidth, screenHeight, selectedDifficulty, selectedMode);

            EndDrawing();

            if (IsKeyPressed(KEY_ESCAPE)) {
                shouldExit = true;
            }
            if (action.openShop) {
                currentScene = Scene::Shop;
            }
            if (action.startGame) {
                gameController.start(selectedDifficulty, selectedMode);
                currentScene = Scene::Game;
            }
        } else if (currentScene == Scene::Game) {
            const auto gameAction = gameController.update(userProfile);
            if (gameAction == game::GameAction::ReturnToMenu) {
                currentScene = Scene::MainMenu;
            }

            const auto& viewState = gameController.getViewState();

            BeginDrawing();
            ClearBackground(RAYWHITE);
            scenes::drawGameScene(screenWidth, screenHeight,
                                  viewState.difficultyLabel,
                                  viewState.modeLabel,
                                  viewState.timerLabel,
                                  viewState.prompt,
                                  viewState.inputBuffer,
                                  viewState.feedback,
                                  viewState.feedbackColor,
                                  viewState.coinsDelta,
                                  viewState.correctAnswers,
                                  viewState.totalQuestions,
                                  userProfile,
                                  mascot);
            EndDrawing();
        } else if (currentScene == Scene::Shop) {
            const int mouseWheel = static_cast<int>(GetMouseWheelMove());
            shopScrollOffset += mouseWheel * 30;
            if (shopScrollOffset > 0) shopScrollOffset = 0;

            if (IsKeyPressed(KEY_ESCAPE)) {
                currentScene = Scene::MainMenu;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            scenes::drawShopScene(screenWidth, screenHeight, shopScrollOffset, userProfile, shopPreviewMascot);
            EndDrawing();
        }
    }

    userProfile.save();
    CloseWindow();

    return 0;
}

}
