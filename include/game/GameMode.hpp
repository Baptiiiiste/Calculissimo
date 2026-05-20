#pragma once

namespace calculissimo::game {

    enum class GameMode {
        Chrono,
        Entrainement
    };

    const char* gameModeToText(GameMode mode);

}

