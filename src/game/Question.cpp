#include "game/Question.hpp"

#include <string>

namespace calculissimo::game {

    /// On récupère le symbole de l'opération pour l'affichage de la question
    std::string operationSymbol(const Operation operation) {
        switch (operation) {
            case Operation::Addition:
                return "+";
            case Operation::Subtraction:
                return "-";
            case Operation::Multiplication:
                return "*";
            case Operation::Division:
                return "/";
        }

        throw std::invalid_argument("Unsupported operation");
    }

    std::string Question::toPrompt() const {
        return std::to_string(leftNumber) + " " + operationSymbol(operation) + " " +
               std::to_string(rightNumber) + " = ?";
    }

}
