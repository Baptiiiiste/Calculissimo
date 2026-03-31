#pragma once

#include "game/Mascot.hpp"
#include "game/QuestionGenerator.hpp"
#include "user/UserProfile.hpp"

namespace calculissimo::core {

  class Application {
    public:
      int run();

    private:
      game::QuestionGenerator questionGenerator;
      user::UserProfile       userProfile{"profile.dat"};
      game::Mascot             mascot{880.0f, 560.0f};
  };

}

