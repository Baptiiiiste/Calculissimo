#pragma once

#include <random>
#include <string>
#include "raylib.h"
#include "game/Difficulty.hpp"
#include "game/GameMode.hpp"
#include "game/Question.hpp"
#include "game/QuestionGenerator.hpp"
#include "user/UserProfile.hpp"

namespace calculissimo::game {

    enum class GameAction {
        None,
        ReturnToMenu,
    };

    struct GameViewState {
        std::string difficultyLabel;
        std::string modeLabel;
        std::string timerLabel;
        std::string prompt;
        std::string inputBuffer;
        std::string feedback;
        Color feedbackColor = DARKGRAY;
        int coinsDelta = 0;
        int correctAnswers = 0;
        int totalQuestions = 0;
    };

    class GameController {
        public:
            GameController();

            void start(Difficulty difficulty, GameMode mode);
            GameAction update(user::UserProfile& userProfile);
            [[nodiscard]] const GameViewState& getViewState() const;

        private:
            QuestionGenerator questionGenerator;
            GameViewState viewState;

            GameMode currentMode = GameMode::Entrainement;
            GenerationSettings settings{};
            Question currentQuestion{};

            std::string inputBuffer;
            std::string feedback;
            Color feedbackColor = DARKGRAY;
            int coinsDelta = 0;
            int correctAnswers = 0;
            int totalQuestions = 0;

            double chronoStartTime = 0.0;
            bool chronoExpired = false;
            bool chronoFinalized = false;

            std::mt19937 randomEngine;
            std::uniform_int_distribution<std::size_t> operationDistribution;

            Operation pickRandomOperation();
            void generateQuestion();
            void refreshViewState();
    };

}
