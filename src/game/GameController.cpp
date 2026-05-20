#include "game/GameController.hpp"

#include <array>
#include <stdexcept>

namespace calculissimo::game {

constexpr int COINS_PER_CORRECT_ANSWER = 10;
constexpr int COINS_PER_WRONG_ANSWER = -2;
constexpr double CHRONO_DURATION_SECONDS = 60.0;

constexpr std::array kOperations{
    Operation::Addition,
    Operation::Subtraction,
    Operation::Multiplication,
    Operation::Division,
};


GameController::GameController(): randomEngine(std::random_device{}()), operationDistribution(0, kOperations.size() - 1) {}

void GameController::start(const Difficulty difficulty, const GameMode mode) {
    currentMode = mode;
    settings = {
        .difficulty = difficulty,
        .operation = pickRandomOperation(),
    };

    inputBuffer.clear();
    feedback.clear();
    feedbackColor = DARKGRAY;
    coinsDelta = 0;
    correctAnswers = 0;
    totalQuestions = 0;
    chronoExpired = false;
    chronoFinalized = false;

    if (currentMode == GameMode::Chrono) {
        chronoStartTime = GetTime();
    }

    generateQuestion();
    refreshViewState();
}

GameAction GameController::update(user::UserProfile& userProfile) {
    GameAction action = GameAction::None;

    if (IsKeyPressed(KEY_ESCAPE)) {
        return GameAction::ReturnToMenu;
    }

    if (currentMode == GameMode::Chrono) {
        const double remainingTime = CHRONO_DURATION_SECONDS - (GetTime() - chronoStartTime);
        if (remainingTime <= 0.0) {
            chronoExpired = true;
        }
    }

    if (chronoExpired) {
        if (!chronoFinalized) {
            feedback = "Temps ecoule ! Score: " + std::to_string(correctAnswers) + "/" + std::to_string(totalQuestions);
            feedbackColor = MAROON;
            chronoFinalized = true;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            action = GameAction::ReturnToMenu;
        }

        refreshViewState();
        return action;
    }

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

            totalQuestions++;
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
            settings.operation = pickRandomOperation();
            generateQuestion();
        } catch (...) {
            feedback = "Entrée invalide";
            feedbackColor = ORANGE;
        }

        inputBuffer.clear();
    }

    refreshViewState();
    return action;
}

const GameViewState& GameController::getViewState() const {
    return viewState;
}

Operation GameController::pickRandomOperation() {
    return kOperations[operationDistribution(randomEngine)];
}

void GameController::generateQuestion() {
    currentQuestion = questionGenerator.generate(settings);
}

void GameController::refreshViewState() {
    viewState.difficultyLabel = std::string("Difficulté: ") + difficultyToText(settings.difficulty);
    viewState.modeLabel = std::string("Mode: ") + gameModeToText(currentMode);
    viewState.prompt = std::string("Question: ") + currentQuestion.toPrompt();
    viewState.inputBuffer = inputBuffer;
    viewState.feedback = feedback;
    viewState.feedbackColor = feedbackColor;
    viewState.coinsDelta = coinsDelta;
    viewState.correctAnswers = correctAnswers;
    viewState.totalQuestions = totalQuestions;

    if (currentMode == GameMode::Chrono) {
        const double remainingTime = std::max(0.0, CHRONO_DURATION_SECONDS - (GetTime() - chronoStartTime));
        const int remainingSeconds = static_cast<int>(std::ceil(remainingTime));
        viewState.timerLabel = "Temps: " + std::to_string(remainingSeconds) + "s";
    } else {
        viewState.timerLabel.clear();
    }
}

}

