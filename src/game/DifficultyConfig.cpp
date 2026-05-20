#include "game/DifficultyConfig.hpp"

#include <stdexcept>

namespace calculissimo::game {

/// Configuration des bornes min & max pour chaque niveau
DifficultyConfig buildDefaultConfig() {
    DifficultyConfig config;
    config.easy = {1, 10};
    config.medium = {5, 20};
    config.hard = {10, 50};
    return config;
}

const DifficultyConfig& getDifficultyConfig() {
    static const DifficultyConfig config = buildDefaultConfig();
    return config;
}

DifficultyRange getDifficultyRange(const Difficulty difficulty, const DifficultyConfig& config) {
    switch (difficulty) {
        case Difficulty::Easy:
            return config.easy;
        case Difficulty::Medium:
            return config.medium;
        case Difficulty::Hard:
            return config.hard;
    }

    throw std::invalid_argument("Unsupported difficulty level");
}

}
