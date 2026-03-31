#include "user/UserProfile.hpp"
#include "storage/FileManager.hpp"
#include <stdexcept>
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
    }
    else {
        coins = 0;
    }
}


void UserProfile::toggleMascotVisibility() {
    mascotVisible = !mascotVisible;
}

/// Appel de la classe de sauvegarde avec les infos du user
void UserProfile::save() const {
    std::unordered_map<std::string, std::string> data;
    data["mascot_visible"] = mascotVisible ? "1" : "0";
    data["coins"] = std::to_string(coins);

    storage::FileManager::save(savePath, data);
}

/// Récupère les infos du user
void UserProfile::loadFromFile() {
    const auto data = storage::FileManager::load(savePath);

    if (data.contains("mascot_visible")) {
        mascotVisible = data.at("mascot_visible") == "1";
    }

    auto tryParseInt = [](const std::string& str, int& out) {
        try {
            std::size_t pos = 0;
            out = std::stoi(str, &pos);
            if (pos != str.size()) {
                out = 0;
            }
        } catch (...) {}
    };

    if (data.contains("coins")) {
        tryParseInt(data.at("coins"), coins);
    }
}

}
