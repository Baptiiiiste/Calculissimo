#include "scenes/ShopScene.hpp"
#include <algorithm>
#include <string>
#include "ui/UiHelper.hpp"

namespace calculissimo::scenes {

void drawShopScene(const int screenWidth, const int screenHeight, const int scrollOffset,
                   user::UserProfile& userProfile,
                   game::Mascot& shopPreviewMascot) {
    DrawText("Boutique", 30, 20, 34, DARKBLUE);

    const std::string coinsText = "Pièces: " + std::to_string(userProfile.getCoins());
    const int coinsWidth = MeasureText(coinsText.c_str(), 24);
    DrawText(coinsText.c_str(), screenWidth - coinsWidth - 30, 25, 24, GOLD);

    DrawText("[ESC] retour | Scroll pour naviguer", 30, 60, 20, GRAY);

    shopPreviewMascot.draw(true, userProfile.getCustomization());

    auto& shopRef = userProfile.getShop();
    const auto& catalogue = shopRef.getCatalogue();

    const int startX = 30;
    const int startY = 100 + scrollOffset;
    const int itemHeight = 40;
    const int buttonWidth = 110;
    const int buttonHeight = 30;

    for (std::size_t i = 0; i < catalogue.size(); ++i) {
        const auto& item = catalogue[i];
        const int yPos = startY + static_cast<int>(i) * itemHeight;

        if (yPos < 80 || yPos > screenHeight) continue;

        DrawText(item.displayName.c_str(), startX, yPos + 5, 20, BLACK);

        const std::string priceText = std::to_string(item.price) + " p.";
        DrawText(priceText.c_str(), startX + 220, yPos + 5, 20, GOLD);

        if (item.color.r != 255 || item.color.g != 255 || item.color.b != 255 || item.color.a != 255) {
            DrawRectangle(startX + 195, yPos + 5, 18, 18, item.color);
            DrawRectangleLines(startX + 195, yPos + 5, 18, 18, BLACK);
        }

        const bool owned = shopRef.isOwned(item.id);
        const bool equipped = std::find(
            userProfile.getEquippedItems().begin(),
            userProfile.getEquippedItems().end(),
            item.id
        ) != userProfile.getEquippedItems().end();

        if (!owned) {
            if (ui::drawButton(startX + 300, yPos, buttonWidth, buttonHeight,
                               "Acheter", DARKGREEN, WHITE)) {
                int currentCoins = userProfile.getCoins();
                if (shopRef.tryBuy(item.id, currentCoins)) {
                    userProfile.setCoins(currentCoins);
                    userProfile.addEquippedItem(item.id);
                    userProfile.save();
                }
            }
        } else if (equipped) {
            if (ui::drawButton(startX + 300, yPos, buttonWidth, buttonHeight,
                               "Retirer", MAROON, WHITE)) {
                userProfile.removeEquippedItem(item.id);
                userProfile.save();
            }
        } else {
            if (ui::drawButton(startX + 300, yPos, buttonWidth, buttonHeight,
                               "Equiper", BLUE, WHITE)) {
                userProfile.addEquippedItem(item.id);
                userProfile.save();
            }
        }
    }
}

}
