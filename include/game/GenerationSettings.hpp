#pragma once
#include "Difficulty.hpp"
#include "Operation.hpp"

namespace calculissimo::game {

    struct GenerationSettings {
        Difficulty difficulty{Difficulty::Easy};
        Operation operation{Operation::Multiplication};
    };

}
