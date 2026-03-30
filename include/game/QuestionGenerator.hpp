#pragma once

#include <random>

#include "GenerationSettings.hpp"
#include "game/Question.hpp"

namespace calculissimo::game {

  class QuestionGenerator {
    public:
      explicit QuestionGenerator(std::uint32_t seed = std::random_device{}());

      Question generate(const GenerationSettings& settings = {});

    private:
      std::mt19937 randomEngine;

      static int getExpectedAnswer(int leftNumber, int rightNumber, Operation operation);
  };

}

