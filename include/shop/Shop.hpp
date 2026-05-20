#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "shop/ShopItem.hpp"
#include "game/MascotCustomization.hpp"

namespace calculissimo::shop {

    class Shop {
        public:
            Shop();

            [[nodiscard]] const std::vector<ShopItem>& getCatalogue() const;
            [[nodiscard]] bool isOwned(const std::string& itemId) const;
            bool tryBuy(const std::string& itemId, int& coins);
            void equip(const std::string& itemId, game::MascotCustomization& customization) const;
            void setOwnedItems(const std::unordered_set<std::string>& items);
            [[nodiscard]] const std::unordered_set<std::string>& getOwnedItems() const;

        private:
            std::vector<ShopItem> catalogue;
            std::unordered_set<std::string> ownedItems;

            void buildCatalogue();
            [[nodiscard]] const ShopItem* findItem(const std::string& itemId) const;
    };

}