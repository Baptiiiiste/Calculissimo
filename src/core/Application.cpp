#include "core/Application.hpp"

#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

namespace calculissimo::core {

int Application::run() {
    std::cout << "Entrez la reponse ou q pour quitter.\n" << std::endl;

    constexpr std::array<game::Operation, 4> operations{
        game::Operation::Addition,
        game::Operation::Subtraction,
        game::Operation::Multiplication,
        game::Operation::Division,
    };

    std::mt19937 randomEngine(std::random_device{}());
    std::uniform_int_distribution<std::size_t> operationDistribution(0, operations.size() - 1);

    int totalQuestions = 0;
    int correctAnswers = 0;

    while (true) {
        const game::GenerationSettings settings{
            .difficulty = game::Difficulty::Easy,
            .operation = operations[operationDistribution(randomEngine)],
        };

        const game::Question question = questionGenerator.generate(settings);
        std::cout << "Question: " << question.toPrompt() <<  std::endl << "> ";

        std::string input;
        if (!(std::cin >> input)) {
            break;
        }

        if (input == "q") {
            break;
        }

        int userAnswer = 0;
        try {
            std::size_t parsedCharacters = 0;
            userAnswer = std::stoi(input, &parsedCharacters);
            if (parsedCharacters != input.size()) {
                throw std::invalid_argument("Input is not an integer");
            }
        } catch (...) {
            std::cout << "Entree invalide\n" << std::endl;
            continue;
        }

        totalQuestions++;
        if (userAnswer == question.expectedAnswer) {
            ++correctAnswers;
            std::cout << "Oui !\n" << std::endl;
        } else {
            std::cout << "Non :( fallait répondre: " << question.expectedAnswer << "\n" << std::endl;
        }
    }

    std::cout << "C'est fini. Score: " << correctAnswers << "/" << totalQuestions << std::endl;

    return 0;
}

}

