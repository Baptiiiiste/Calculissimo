#pragma once

#include "raylib.h"
#include <string>

namespace calculissimo::game {

    struct MascotCustomization {
        Color eyeColor  = BLACK;
        Color bodyColor = BLUE;
        Color headColor = BEIGE;
        Color hatColor  = RED;
        Color hairColor = BROWN;
        Color sunglassesColor = BLACK;

        bool hasHat = false;
        bool hasHair = false;
        bool hasSunglasses = false;


    };

}
