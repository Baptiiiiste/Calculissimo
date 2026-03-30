#pragma once

#include <string>
#include "Operation.hpp"

namespace calculissimo::game {

    struct Question {
        int leftNumber{};
        int rightNumber{};
        Operation operation{Operation::Multiplication};
        int expectedAnswer{};

        [[nodiscard]] std::string toPrompt() const;
    };

}

