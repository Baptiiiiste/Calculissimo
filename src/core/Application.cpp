#include "core/Application.hpp"
#include <array>
#include <random>
#include <stdexcept>
#include <string>
#include "raylib.h"

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
    while (!WindowShouldClose()) {
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
                    feedback = "Oui bien joué :)";
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

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Calculissimo", 30, 20, 34, DARKBLUE);
        const std::string difficultyLabel = std::string("Difficulté: ") + game::difficultyToText(settings.difficulty);
        const int difficultyTextWidth = MeasureText(difficultyLabel.c_str(), 20);
        DrawText(difficultyLabel.c_str(), (screenWidth - difficultyTextWidth - 30), 20, 20, DARKGRAY);
        DrawText("[ESC] quitter | [ENTREE] valider | [?] mascotte", 30, 65, 20, GRAY);

        const std::string prompt = "Question: " + currentQuestion.toPrompt();
        DrawText(prompt.c_str(), 30, 150, 40, BLACK);

        DrawRectangleLines(30, 230, 380, 60, DARKGRAY);
        const std::string inputLabel = "Reponse: " + inputBuffer;
        DrawText(inputLabel.c_str(), 45, 247, 28, BLACK);

        DrawText(feedback.c_str(), 30, 320, 26, feedbackColor);

        const std::string scoreText = "Score: " + std::to_string(correctAnswers) + "/" + std::to_string(totalQuestions);
        DrawText(scoreText.c_str(), 30, 380, 30, MAROON);

        const std::string coinsText = "Pièces: " + std::to_string(userProfile.getCoins());
        DrawText(coinsText.c_str(), 30, 420, 24, GOLD);

        if (coinsDelta != 0) {
            const int coinsTextWidth = MeasureText(coinsText.c_str(), 24);
            const std::string deltaText = (coinsDelta > 0)
                ? " +" + std::to_string(coinsDelta)
                : " " + std::to_string(coinsDelta);
            const Color deltaColor = (coinsDelta > 0) ? GREEN : RED;
            DrawText(deltaText.c_str(), 30 + coinsTextWidth, 420, 24, deltaColor);
        }


        mascot.draw(userProfile.isMascotVisible());

        EndDrawing();
    }

    userProfile.save();
    CloseWindow();

    return 0;
}

}

