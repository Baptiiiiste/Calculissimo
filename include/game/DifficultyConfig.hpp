#pragma once

#include "game/Difficulty.hpp"

namespace calculissimo::game {

    struct DifficultyRange {
        int minValue = 1;
        int maxValue = 10;
    };

    struct DifficultyConfig {
        DifficultyRange easy{1, 10};
        DifficultyRange medium{5, 20};
        DifficultyRange hard{10, 50};
    };

    const DifficultyConfig& getDifficultyConfig();
    DifficultyRange getDifficultyRange(Difficulty difficulty, const DifficultyConfig& config);

}
