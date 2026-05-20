#include "core/Application.hpp"

#include <array>
#include <random>
#include <stdexcept>
#include <string>
#include "raylib.h"
#include "scenes/GameScene.hpp"
#include "scenes/ShopScene.hpp"

namespace calculissimo::core {

static constexpr int COINS_PER_CORRECT_ANSWER = 10;
static constexpr int COINS_PER_WRONG_ANSWER = -2;

int Application::run() {
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Calculissimo");
    SetTargetFPS(60);

    constexpr std::array<game::Operation, 4> operations{
        game::Operation::Addition,
        game::Operation::Subtraction,
        game::Operation::Multiplication,
        game::Operation::Division,
    };

    std::mt19937 randomEngine(std::random_device{}());
    std::uniform_int_distribution<std::size_t> operationDistribution(0, operations.size() - 1);

    game::GenerationSettings settings{
        .difficulty = game::Difficulty::Easy,
        .operation = operations[operationDistribution(randomEngine)],
    };
    game::Question currentQuestion = questionGenerator.generate(settings);

    std::string inputBuffer;
    std::string feedback;
    Color feedbackColor = DARKGRAY;

    int coinsDelta = 0;
    int correctAnswers = 0;
    int totalQuestions = 0;
    int shopScrollOffset = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_B)) {
            currentScene = (currentScene == Scene::Game) ? Scene::Shop : Scene::Game;
        }

        if (currentScene == Scene::Game) {
            int key = GetCharPressed();
            while (key > 0) {
                const bool isDigit = key >= '0' && key <= '9';
                const bool isNegativeSign = key == '-' && inputBuffer.empty();

                if (isDigit || isNegativeSign) {
                    inputBuffer.push_back(static_cast<char>(key));
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !inputBuffer.empty()) {
                inputBuffer.pop_back();
            }

            if (IsKeyPressed(KEY_M)) {
                userProfile.toggleMascotVisibility();
                userProfile.save();
            }

            if (IsKeyPressed(KEY_ENTER)) {
                try {
                    std::size_t parsedCharacters = 0;
                    const int answer = std::stoi(inputBuffer, &parsedCharacters);
                    if (parsedCharacters != inputBuffer.size()) {
                        throw std::invalid_argument("Not a pure integer");
                    }

                    ++totalQuestions;
                    if (answer == currentQuestion.expectedAnswer) {
                        coinsDelta = COINS_PER_CORRECT_ANSWER;
                        userProfile.addCoins(COINS_PER_CORRECT_ANSWER);
                        feedback = "Oui bien jou\xc3\xa9 :)";
                        feedbackColor = GREEN;
                        correctAnswers++;
                    } else {
                        coinsDelta = COINS_PER_WRONG_ANSWER;
                        userProfile.addCoins(COINS_PER_WRONG_ANSWER);
                        feedback = "Non :( c'est faux. Reponse: " + std::to_string(currentQuestion.expectedAnswer);
                        feedbackColor = RED;
                    }

                    userProfile.save();

                    currentQuestion = questionGenerator.generate({
                        .difficulty = game::Difficulty::Easy,
                        .operation = operations[operationDistribution(randomEngine)],
                    });
                } catch (...) {
                    feedback = "Entree invalide";
                    feedbackColor = ORANGE;
                }

                inputBuffer.clear();
            }
        } else {
            const int mouseWheel = static_cast<int>(GetMouseWheelMove());
            shopScrollOffset += mouseWheel * 30;
            if (shopScrollOffset > 0) shopScrollOffset = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScene == Scene::Game) {
            const std::string difficultyLabel = std::string("Difficult\xc3\xa9: ") + game::difficultyToText(settings.difficulty);
            const std::string prompt = "Question: " + currentQuestion.toPrompt();
            scenes::drawGameScene(screenWidth, screenHeight, difficultyLabel, prompt,
                                  inputBuffer, feedback, feedbackColor, coinsDelta,
                                  correctAnswers, totalQuestions, userProfile, mascot);
        } else {
            scenes::drawShopScene(screenWidth, screenHeight, shopScrollOffset,
                                  userProfile, shopPreviewMascot);
        }

        EndDrawing();
    }

    userProfile.save();
    CloseWindow();

    return 0;
}

}

