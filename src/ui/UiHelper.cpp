#include "ui/UiHelper.hpp"

#include <algorithm>

namespace calculissimo::ui {

bool drawButton(const int x, const int y, const int width, const int height,
                const char* text, const Color bgColor, const Color textColor) {
    const Rectangle rect = {static_cast<float>(x), static_cast<float>(y),
                            static_cast<float>(width), static_cast<float>(height)};
    const Vector2 mouse = GetMousePosition();
    const bool hovered = CheckCollisionPointRec(mouse, rect);

    const Color drawColor = hovered
        ? Color{
            static_cast<unsigned char>(std::min(bgColor.r + 40, 255)),
            static_cast<unsigned char>(std::min(bgColor.g + 40, 255)),
            static_cast<unsigned char>(std::min(bgColor.b + 40, 255)),
            bgColor.a}
        : bgColor;

    DrawRectangleRounded(rect, 0.3f, 6, drawColor);
    DrawRectangleRoundedLinesEx(rect, 0.3f, 6, 2.0f, BLACK);

    const int textWidth = MeasureText(text, 18);
    DrawText(text, x + (width - textWidth) / 2, y + (height - 18) / 2, 18, textColor);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

}
