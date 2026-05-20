#include "game/GameMode.hpp"

#include <stdexcept>

namespace calculissimo::game {

const char* gameModeToText(const GameMode mode) {
    switch (mode) {
        case GameMode::Chrono:
            return "Chrono";
        case GameMode::Entrainement:
            return "Entrainement";
    }

    throw std::invalid_argument("Unsupported game mode");
}

}

