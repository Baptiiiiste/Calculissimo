#include "game/QuestionGenerator.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include "game/DifficultyConfig.hpp"

namespace calculissimo::game {


/// On récupère une paire de nombres aléatoires en fonction de la difficulté qui serviront de bornes
std::pair<int, int> rangeForDifficulty(const Difficulty difficulty) {
    const auto& config = getDifficultyConfig();
    const auto range = getDifficultyRange(difficulty, config);
    return {range.minValue, range.maxValue};
}

/// Constructeur avec un seed aléatoire pour la génération des questions, ca évitera qu'on ait les mêmes nombres à chaque fois
QuestionGenerator::QuestionGenerator(const std::uint32_t seed) : randomEngine(seed) {}

/// Génère une question en fonction des paramètres
Question QuestionGenerator::generate(const GenerationSettings& settings) {
    const auto [minValue, maxValue] = rangeForDifficulty(settings.difficulty);
    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    int leftNumber = distribution(randomEngine);
    int rightNumber = distribution(randomEngine);

    if (settings.operation == Operation::Division) {
        std::uniform_int_distribution<int> divisorDistribution(std::max(1, minValue), maxValue);
        std::uniform_int_distribution<int> quotientDistribution(minValue, maxValue);

        rightNumber = divisorDistribution(randomEngine);
        const int quotient = quotientDistribution(randomEngine);
        leftNumber = rightNumber * quotient;
    }

    return {
        .leftNumber = leftNumber,
        .rightNumber = rightNumber,
        .operation = settings.operation,
        .expectedAnswer = getExpectedAnswer(leftNumber, rightNumber, settings.operation),
    };
}

/// Donne le résultat attendu
int QuestionGenerator::getExpectedAnswer(const int leftNumber, const int rightNumber, const Operation operation) {
    switch (operation) {
    case Operation::Addition:
        return leftNumber + rightNumber;
    case Operation::Subtraction:
        return leftNumber - rightNumber;
    case Operation::Multiplication:
        return leftNumber * rightNumber;
    case Operation::Division:
        if (rightNumber == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return leftNumber / rightNumber;
    }

    throw std::invalid_argument("Unsupported operation");
}

}
