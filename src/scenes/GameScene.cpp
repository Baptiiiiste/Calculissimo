#include "scenes/GameScene.hpp"

namespace calculissimo::scenes {

void drawGameScene(const int screenWidth, const int screenHeight,
                   const std::string& difficultyLabel,
                   const std::string& modeLabel,
                   const std::string& timerLabel,
                   const std::string& prompt,
                   const std::string& inputBuffer,
                   const std::string& feedback,
                   const Color feedbackColor,
                   const int coinsDelta,
                   const int correctAnswers,
                   const int totalQuestions,
                   user::UserProfile& userProfile,
                   game::Mascot& mascot) {
    DrawText("Calculissimo", 30, 20, 34, DARKBLUE);

    const int difficultyTextWidth = MeasureText(difficultyLabel.c_str(), 20);
    DrawText(difficultyLabel.c_str(), screenWidth - difficultyTextWidth - 30, 20, 20, DARKGRAY);

    const int modeTextWidth = MeasureText(modeLabel.c_str(), 20);
    DrawText(modeLabel.c_str(), screenWidth - modeTextWidth - 30, 45, 20, DARKGRAY);

    if (!timerLabel.empty()) {
        const int timerTextWidth = MeasureText(timerLabel.c_str(), 20);
        DrawText(timerLabel.c_str(), screenWidth - timerTextWidth - 30, 70, 20, MAROON);
    }

    DrawText("[ESC] menu | [ENTREE] valider | [?] mascotte", 30, 95, 20, GRAY);

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

    mascot.draw(userProfile.isMascotVisible(), userProfile.getCustomization());
}

}
