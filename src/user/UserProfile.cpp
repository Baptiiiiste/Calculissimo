#include "user/UserProfile.hpp"
#include "storage/FileManager.hpp"
#include <algorithm>
#include <sstream>
#include <string>

namespace calculissimo::user {

UserProfile::UserProfile(std::string savePath): savePath(std::move(savePath)) {
    loadFromFile();
}

bool UserProfile::isMascotVisible() const {
    return mascotVisible;
}

int  UserProfile::getCoins() const {
    return coins;
}

void UserProfile::setMascotVisible(const bool visible) {
    mascotVisible = visible;
}

void UserProfile::addCoins(const int amount) {
    if (coins + amount >= 0) {
        coins += amount;
    } else {
        coins = 0;
    }
}

void UserProfile::setCoins(const int value) {
    coins = (value >= 0) ? value : 0;
}

void UserProfile::toggleMascotVisibility() {
    mascotVisible = !mascotVisible;
}

game::MascotCustomization& UserProfile::getCustomization() {
    return customization;
}

const game::MascotCustomization& UserProfile::getCustomization() const {
    return customization;
}

/// Définit les items équipés et reconstruit la customisation
void UserProfile::setEquippedItems(const std::vector<std::string>& items) {
    equippedItems = items;
    rebuildCustomization();
}

const std::vector<std::string>& UserProfile::getEquippedItems() const {
    return equippedItems;
}

/// Ajoute un nouvel items & reconstruit
void UserProfile::addEquippedItem(const std::string& itemId) {
    if (std::ranges::find(equippedItems, itemId) == equippedItems.end()) {
        equippedItems.push_back(itemId);
    }
    rebuildCustomization();
}

void UserProfile::removeEquippedItem(const std::string& itemId) {
    std::erase(equippedItems, itemId);
    rebuildCustomization();
}

shop::Shop& UserProfile::getShop() { return shop; }

/// Rajoute les objets sélectionné à la mascotte
void UserProfile::rebuildCustomization() {
    customization = game::MascotCustomization{};
    for (const auto& itemId : equippedItems) {
        shop.equip(itemId, customization);
    }
}

void UserProfile::save() const {
    std::unordered_map<std::string, std::string> data;
    data["mascot_visible"] = mascotVisible ? "1" : "0";
    data["coins"] = std::to_string(coins);

    // Format des items achetés par id: "item1,item2,item3"
    {
        std::string owned;
        for (const auto& id : shop.getOwnedItems()) {
            if (!owned.empty()) owned += ',';
            owned += id;
        }
        data["owned_items"] = owned;
    }

    // Format des items équipés par id: "item1,item2,item3"
    {
        std::string equipped;
        for (const auto& id : equippedItems) {
            if (!equipped.empty()) equipped += ',';
            equipped += id;
        }
        data["equipped_items"] = equipped;
    }

    storage::FileManager::save(savePath, data);
}

/// Charge les données depuis le fichier
void UserProfile::loadFromFile() {
    const auto data = storage::FileManager::load(savePath);

    if (data.contains("mascot_visible")) {
        mascotVisible = data.at("mascot_visible") == "1";
    }

    auto tryParseInt = [](const std::string& str, int& out) {
        try {
            std::size_t pos = 0;
            out = std::stoi(str, &pos);
            if (pos != str.size()) out = 0;
        } catch (...) {}
    };

    if (data.contains("coins")) {
        tryParseInt(data.at("coins"), coins);
    }

    auto splitString = [](const std::string& str, char delimiter) -> std::vector<std::string> {
        std::vector<std::string> tokens;
        std::istringstream stream(str);
        std::string token;
        while (std::getline(stream, token, delimiter)) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    };

    if (data.contains("owned_items") && !data.at("owned_items").empty()) {
        auto ownedList = splitString(data.at("owned_items"), ',');
        std::unordered_set<std::string> ownedSet(ownedList.begin(), ownedList.end());
        shop.setOwnedItems(ownedSet);
    }

    if (data.contains("equipped_items") && !data.at("equipped_items").empty()) {
        equippedItems = splitString(data.at("equipped_items"), ',');
        rebuildCustomization();
    }
}

}
