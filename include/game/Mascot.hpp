#pragma once

namespace calculissimo::game {

    class Mascot {
        public:
            Mascot(float posX, float posY);
            void draw(bool visible) const;

        private:
            float x;
            float y;

            void drawBody() const;
            void drawHead() const;
            void drawEyes() const;
    };

}
