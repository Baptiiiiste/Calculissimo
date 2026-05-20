#pragma once

#include "game/Mascot.hpp"
#include "user/UserProfile.hpp"

namespace calculissimo::scenes {

    void drawShopScene(int screenWidth, int screenHeight, int scrollOffset, user::UserProfile& userProfile, game::Mascot& shopPreviewMascot);

}
