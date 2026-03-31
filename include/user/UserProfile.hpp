#pragma once

#include <string>

namespace calculissimo::user {

    class UserProfile {
        public:
            explicit UserProfile(std::string savePath = "profile.dat");

            [[nodiscard]] bool isMascotVisible() const;
            [[nodiscard]] int  getCoins() const;

            void setMascotVisible(bool visible);
            void addCoins(int amount);
            void toggleMascotVisibility();
            void save() const;

        private:
            std::string savePath;
            bool mascotVisible = true;
            int  coins = 0;

            void loadFromFile();
    };

}
