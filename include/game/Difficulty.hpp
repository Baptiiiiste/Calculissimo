#pragma once

namespace calculissimo::game {

    enum class Difficulty {
        Easy,
        Medium,
        Hard
    };

    const char* difficultyToText(Difficulty difficulty);

}