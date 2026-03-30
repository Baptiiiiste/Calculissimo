#include "game/Difficulty.hpp"

#include <stdexcept>

namespace calculissimo::game {
    const char* difficultyToText(const Difficulty difficulty) {
        switch (difficulty) {
            case Difficulty::Easy:
                return "Facile";
            case Difficulty::Medium:
                return "Moyen";
            case Difficulty::Hard:
                return "Difficile";
        }

        throw std::invalid_argument("Unsupported difficulty");
    }
}

