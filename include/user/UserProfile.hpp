#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "game/MascotCustomization.hpp"
#include "shop/Shop.hpp"

namespace calculissimo::user {

class UserProfile {
public:
    explicit UserProfile(std::string savePath = "profile.dat");

    [[nodiscard]] bool isMascotVisible() const;
    [[nodiscard]] int  getCoins() const;
    void setMascotVisible(bool visible);
    void addCoins(int amount);
    void setCoins(int value);
    void toggleMascotVisibility();

    // Customisation mascotte & shop
    [[nodiscard]] game::MascotCustomization& getCustomization();
    [[nodiscard]] const game::MascotCustomization& getCustomization() const;
    void setEquippedItems(const std::vector<std::string>& items);
    [[nodiscard]] const std::vector<std::string>& getEquippedItems() const;
    void addEquippedItem(const std::string& itemId);
    void removeEquippedItem(const std::string& itemId);
    [[nodiscard]] shop::Shop& getShop();

    void save() const;

private:
    std::string savePath;

    bool mascotVisible = true;
    int  coins = 0;

    game::MascotCustomization customization;
    std::vector<std::string> equippedItems;
    shop::Shop shop;

    void loadFromFile();
    void rebuildCustomization();
};

}
