#include "game/Mascot.hpp"
#include "raylib.h"

namespace calculissimo::game {

Mascot::Mascot(const float posX, const float posY): x(posX), y(posY) {}

// Dessine la mascotte si elle est visible
void Mascot::draw(const bool visible) const {
    if (!visible) {
        return;
    }

    drawBody();
    drawHead();
    drawEyes();
}


/// Dessine le corps et les bras.
void Mascot::drawBody() const {

    const float bodyWidth  = 50.0f;
    const float bodyHeight = 60.0f;
    const float bodyX = x - bodyWidth / 2.0f;
    const float bodyY = y - bodyHeight - 40.0f;

    DrawRectangleRounded(
        {bodyX, bodyY, bodyWidth, bodyHeight},
        0.3f, 6, BLUE
    );

    // Bras gauche
    DrawLineEx(
        {bodyX, bodyY + 15.0f},
        {bodyX - 20.0f, bodyY + 45.0f},
        3.0f, DARKBLUE
    );

    // Bras droit
    DrawLineEx(
        {bodyX + bodyWidth, bodyY + 15.0f},
        {bodyX + bodyWidth + 20.0f, bodyY + 45.0f},
        3.0f, DARKBLUE
    );

    // Jambe gauche
    DrawLineEx(
        {x - 10.0f, y - 40.0f},
        {x - 15.0f, y - 10.0f},
        3.0f, DARKBLUE
    );

    // Jambe droite
    DrawLineEx(
        {x + 10.0f, y - 40.0f},
        {x + 15.0f, y - 10.0f},
        3.0f, DARKBLUE
    );
}

/// Dessine la tête
void Mascot::drawHead() const {
    const float headRadius = 28.0f;
    const float headCenterY = y - 60.0f - 40.0f - headRadius + 5.0f;

    DrawCircle(
        static_cast<int>(x),
        static_cast<int>(headCenterY),
        headRadius, BEIGE
    );

    // Contour
    DrawCircleLines(
        static_cast<int>(x),
        static_cast<int>(headCenterY),
        headRadius, BLACK
    );

    // Bouche
    const float mouthY = headCenterY + 10.0f;
    DrawLineEx({x - 8.0f, mouthY}, {x - 3.0f, mouthY + 4.0f}, 2.0f, BLACK);
    DrawLineEx({x - 3.0f, mouthY + 4.0f},{x + 3.0f, mouthY + 4.0f}, 2.0f, BLACK);
    DrawLineEx({x + 3.0f, mouthY + 4.0f},{x + 8.0f, mouthY}, 2.0f, BLACK);
}

/// Dessine les yeux
void Mascot::drawEyes() const {
    const float headCenterY = y - 60.0f - 40.0f - 28.0f + 5.0f;

    // Œil gauche
    DrawCircle(static_cast<int>(x - 9.0f), static_cast<int>(headCenterY - 5.0f), 6.0f, WHITE);
    DrawCircle(static_cast<int>(x - 9.0f), static_cast<int>(headCenterY - 5.0f), 3.0f, BLACK);

    // Œil droit
    DrawCircle(static_cast<int>(x + 9.0f), static_cast<int>(headCenterY - 5.0f), 6.0f, WHITE);
    DrawCircle(static_cast<int>(x + 9.0f), static_cast<int>(headCenterY - 5.0f), 3.0f, BLACK);
}

}
