#pragma once
#include "game/MascotCustomization.hpp"

namespace calculissimo::game {

class Mascot {
public:
    Mascot(float posX, float posY);
    void draw(bool visible, const MascotCustomization& custom = {}) const;

private:
    float x;
    float y;

    void drawBody(const MascotCustomization& custom) const;
    void drawHead(const MascotCustomization& custom) const;
    void drawEyes(const MascotCustomization& custom) const;
    void drawHat(const MascotCustomization& custom) const;
    void drawHair(const MascotCustomization& custom) const;
    void drawSunglasses() const;
};

}
