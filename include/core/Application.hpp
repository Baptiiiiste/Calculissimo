#pragma once

#include "game/QuestionGenerator.hpp"

namespace calculissimo::core {

  class Application {
    public:
      int run();

    private:
      game::QuestionGenerator questionGenerator;
  };

}

