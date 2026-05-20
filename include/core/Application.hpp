#pragma once

#include "core/Scene.hpp"
#include "game/GameController.hpp"
#include "game/GameMode.hpp"
#include "game/Mascot.hpp"
#include "user/UserProfile.hpp"

namespace calculissimo::core {

  class Application {
    public:
      int run();

    private:
      game::GameController gameController;
      user::UserProfile     userProfile{"profile.dat"};
      game::Mascot          mascot{880.0f, 560.0f};
      game::Mascot          shopPreviewMascot{700.0f, 450.0f};

      game::Difficulty selectedDifficulty = game::Difficulty::Easy;
      game::GameMode selectedMode = game::GameMode::Entrainement;

      Scene currentScene = Scene::MainMenu;
  };

}
