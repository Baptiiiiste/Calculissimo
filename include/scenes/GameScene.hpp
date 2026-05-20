#pragma once

#include <string>
#include "raylib.h"
#include "game/Mascot.hpp"
#include "user/UserProfile.hpp"

namespace calculissimo::scenes {

    void drawGameScene(int screenWidth, int screenHeight,
                        const std::string& difficultyLabel,
                        const std::string& modeLabel,
                        const std::string& timerLabel,
                        const std::string& prompt,
                        const std::string& inputBuffer,
                        const std::string& feedback,
                        Color feedbackColor,
                        int coinsDelta,
                        int correctAnswers,
                        int totalQuestions,
                        user::UserProfile& userProfile,
                        game::Mascot& mascot);

}
