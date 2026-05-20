#include "game/Mascot.hpp"
#include "raylib.h"

namespace calculissimo::game {

Mascot::Mascot(const float posX, const float posY): x(posX), y(posY) {}

// Dessine la mascotte si elle est visible
void Mascot::draw(const bool visible, const MascotCustomization& custom) const {
    if (!visible) {
        return;
    }

    drawBody(custom);
    if (custom.hasHair) {
        drawHair(custom);
    }
    drawHead(custom);
    drawEyes(custom);
    if (custom.hasSunglasses) {
        drawSunglasses();
    }
    if (custom.hasHat) {
        drawHat(custom);
    }
}

/// Dessine le corps et les bras.
void Mascot::drawBody(const MascotCustomization& custom) const {
    const float bodyWidth  = 50.0f;
    const float bodyHeight = 60.0f;
    const float bodyX = x - bodyWidth / 2.0f;
    const float bodyY = y - bodyHeight - 40.0f;

    DrawRectangleRounded(
        {bodyX, bodyY, bodyWidth, bodyHeight},
        0.3f, 6, custom.bodyColor
    );

    const Color limbColor = {
        static_cast<unsigned char>(custom.bodyColor.r / 2),
        static_cast<unsigned char>(custom.bodyColor.g / 2),
        static_cast<unsigned char>(custom.bodyColor.b / 2),
        255
    };

    // Bras gauche
    DrawLineEx(
        {bodyX, bodyY + 15.0f},
        {bodyX - 20.0f, bodyY + 45.0f},
        3.0f, limbColor
    );

    // Bras droit
    DrawLineEx(
        {bodyX + bodyWidth, bodyY + 15.0f},
        {bodyX + bodyWidth + 20.0f, bodyY + 45.0f},
        3.0f, limbColor
    );

    // Jambe gauche
    DrawLineEx(
        {x - 10.0f, y - 40.0f},
        {x - 15.0f, y - 10.0f},
        3.0f, limbColor
    );

    // Jambe droite
    DrawLineEx(
        {x + 10.0f, y - 40.0f},
        {x + 15.0f, y - 10.0f},
        3.0f, limbColor
    );
}

/// Dessine la tête
void Mascot::drawHead(const MascotCustomization& custom) const {
    const float headRadius = 28.0f;
    const float headCenterY = y - 60.0f - 40.0f - headRadius + 5.0f;

    DrawCircle(
        static_cast<int>(x),
        static_cast<int>(headCenterY),
        headRadius, custom.headColor
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
void Mascot::drawEyes(const MascotCustomization& custom) const {
    const float headCenterY = y - 60.0f - 40.0f - 28.0f + 5.0f;

    // Œil gauche
    DrawCircle(static_cast<int>(x - 9.0f), static_cast<int>(headCenterY - 5.0f), 6.0f, WHITE);
    DrawCircle(static_cast<int>(x - 9.0f), static_cast<int>(headCenterY - 5.0f), 3.0f, custom.eyeColor);

    // Œil droit
    DrawCircle(static_cast<int>(x + 9.0f), static_cast<int>(headCenterY - 5.0f), 6.0f, WHITE);
    DrawCircle(static_cast<int>(x + 9.0f), static_cast<int>(headCenterY - 5.0f), 3.0f, custom.eyeColor);
}

/// Dessine le chapeau
void Mascot::drawHat(const MascotCustomization& custom) const {
    const float headCenterY = y - 60.0f - 40.0f - 28.0f + 5.0f;
    const float hatBaseY = headCenterY - 28.0f;

    // Bord du chapeau
    DrawRectangle(
        static_cast<int>(x - 30.0f),
        static_cast<int>(hatBaseY - 2.0f),
        60, 6, custom.hatColor
    );

    // Haut du chapeau
    DrawRectangleRounded(
        {x - 20.0f, hatBaseY - 22.0f, 40.0f, 22.0f},
        0.4f, 6, custom.hatColor
    );
}

/// Dessine les cheveux
void Mascot::drawHair(const MascotCustomization& custom) const {
    const float headCenterY = y - 60.0f - 40.0f - 28.0f + 5.0f;
    const float hairTopY = headCenterY - 28.0f;

    for (int i = -2; i <= 2; ++i) {
        const float offsetX = static_cast<float>(i) * 8.0f;
        DrawLineEx(
            {x + offsetX, hairTopY + 5.0f},
            {x + offsetX + 3.0f, hairTopY - 10.0f},
            3.0f, custom.hairColor
        );
    }

    DrawLineEx({x - 26.0f, headCenterY - 10.0f}, {x - 32.0f, headCenterY + 5.0f}, 3.0f, custom.hairColor);
    DrawLineEx({x + 26.0f, headCenterY - 10.0f}, {x + 32.0f, headCenterY + 5.0f}, 3.0f, custom.hairColor);
}

/// Dessine les lunettes
void Mascot::drawSunglasses() const {
    const float headCenterY = y - 60.0f - 40.0f - 28.0f + 5.0f;
    const float glassY = headCenterY - 10.0f;

    // Verre gauche
    DrawRectangleRounded(
        {x - 18.0f, glassY, 14.0f, 10.0f},
        0.3f, 4, BLACK
    );

    // Verre droit
    DrawRectangleRounded(
        {x + 4.0f, glassY, 14.0f, 10.0f},
        0.3f, 4, BLACK
    );

    // Barre entre les verres
    DrawLineEx({x - 4.0f, glassY + 5.0f}, {x + 4.0f, glassY + 5.0f}, 2.0f, BLACK);

    // Branches
    DrawLineEx({x - 18.0f, glassY + 3.0f}, {x - 28.0f, glassY + 1.0f}, 2.0f, BLACK);
    DrawLineEx({x + 18.0f, glassY + 3.0f}, {x + 28.0f, glassY + 1.0f}, 2.0f, BLACK);
}

}
