#include "shop/Shop.hpp"

#include <algorithm>

namespace calculissimo::shop {

Shop::Shop() {
    buildCatalogue();
}

const std::vector<ShopItem>& Shop::getCatalogue() const {
    return catalogue;
}

bool Shop::isOwned(const std::string& itemId) const {
    return ownedItems.contains(itemId);
}

/// Essaye d'acheter si le user a l'argent & n'a pas déjà l'item
bool Shop::tryBuy(const std::string& itemId, int& coins) {
    const ShopItem* item = findItem(itemId);
    if (!item) return false;
    if (isOwned(itemId)) return false;
    if (coins < item->price) return false;

    coins -= item->price;
    ownedItems.insert(itemId);
    return true;
}

/// Ajoute aux settings de la mascotte l'item
void Shop::equip(const std::string& itemId, game::MascotCustomization& customization) const {
    const ShopItem* item = findItem(itemId);
    if (!item) return;

    switch (item->category) {
        case ItemCategory::EyeColor:
            customization.eyeColor = item->color;
            break;
        case ItemCategory::BodyColor:
            customization.bodyColor = item->color;
            break;
        case ItemCategory::HeadColor:
            customization.headColor = item->color;
            break;
        case ItemCategory::Hat:
            customization.hasHat = true;
            break;
        case ItemCategory::Hair:
            customization.hasHair = true;
            break;
        case ItemCategory::Sunglasses:
            customization.hasSunglasses = true;
            break;
        case ItemCategory::HatColor:
            customization.hatColor = item->color;
            break;
        case ItemCategory::HairColor:
            customization.hairColor = item->color;
            break;
    }
}

void Shop::setOwnedItems(const std::unordered_set<std::string>& items) {
    ownedItems = items;
}

const std::unordered_set<std::string>& Shop::getOwnedItems() const {
    return ownedItems;
}

/// Crée le catalogue de tous les items avec le prix
void Shop::buildCatalogue() {
    // Yeux
    catalogue.push_back({"eye_blue", "Yeux bleus", ItemCategory::EyeColor, 200, BLUE});
    catalogue.push_back({"eye_green", "Yeux verts", ItemCategory::EyeColor, 200, DARKGREEN});
    catalogue.push_back({"eye_red", "Yeux rouges", ItemCategory::EyeColor, 300, RED});
    catalogue.push_back({"eye_purple", "Yeux violets", ItemCategory::EyeColor, 400,  PURPLE});

    // Corps
    catalogue.push_back({"body_red", "T-shirt rouge", ItemCategory::BodyColor, 300, RED});
    catalogue.push_back({"body_green", "T-shirt vert", ItemCategory::BodyColor, 300, DARKGREEN});
    catalogue.push_back({"body_purple", "T-shirt violet", ItemCategory::BodyColor, 400, PURPLE});
    catalogue.push_back({"body_orange", "T-shirt orange",  ItemCategory::BodyColor, 300, ORANGE});

    // Tete
    catalogue.push_back({"head_pink", "Peau rose", ItemCategory::HeadColor, 250, PINK});
    catalogue.push_back({"head_brown", "Peau marron", ItemCategory::HeadColor, 250, BROWN});
    catalogue.push_back({"head_pale", "Peau claire", ItemCategory::HeadColor, 250, {255, 228, 196, 255}});

    // Accessoires
    catalogue.push_back({"hat_on", "Chapeau", ItemCategory::Hat, 500, RED});
    catalogue.push_back({"hair_on", "Cheveux", ItemCategory::Hair, 400,BROWN});
    catalogue.push_back({"sunglasses_on", "Lunettes de soleil", ItemCategory::Sunglasses, 600, BLACK});

    // Chapeau
    catalogue.push_back({"hat_blue", "Chapeau bleu", ItemCategory::HatColor, 200, BLUE});
    catalogue.push_back({"hat_green", "Chapeau vert", ItemCategory::HatColor, 200, DARKGREEN});
    catalogue.push_back({"hat_purple", "Chapeau violet", ItemCategory::HatColor, 300, PURPLE});
    catalogue.push_back({"hat_gold",   "Chapeau de riche", ItemCategory::HatColor, 500, GOLD});

    // Cheveux
    catalogue.push_back({"hair_blond", "Cheveux blonds", ItemCategory::HairColor, 200, {255, 215, 0, 255}});
    catalogue.push_back({"hair_black", "Cheveux noirs",  ItemCategory::HairColor, 150, BLACK});
    catalogue.push_back({"hair_red", "Cheveux roux", ItemCategory::HairColor, 250, {178, 34, 34, 255}});
    catalogue.push_back({"hair_blue", "Cheveux bleus",  ItemCategory::HairColor, 350, BLUE});
}

/// Récupère un objet dans le shop a partir de son id
const ShopItem* Shop::findItem(const std::string& itemId) const {
    auto it = std::find_if(catalogue.begin(), catalogue.end(),
        [&itemId](const ShopItem& item) { return item.id == itemId; });

    return (it != catalogue.end()) ? &(*it) : nullptr;
}

}
