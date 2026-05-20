#pragma once

#include <string>
#include "ItemCategory.h"
#include "raylib.h"

namespace calculissimo::shop {

    struct ShopItem {
        std::string id;
        std::string displayName;
        ItemCategory category;
        int price;
        Color color{WHITE};
    };

}
