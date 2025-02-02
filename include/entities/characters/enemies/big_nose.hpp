#pragma once
#include "enemy.hpp"
#include "../../../lists/circular.hpp"

using namespace sf;

namespace entities::characters
{
    class BigNose : public Enemy
    {
    private:
        int sneezePower;

    public:
        BigNose();
        BigNose(const int x, const int y);
        ~BigNose();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        void collideX();
        int getAttack();
        void slowness();
        void burn();
    };
}
