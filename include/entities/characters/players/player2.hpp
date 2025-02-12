#pragma once
#include "player.hpp"

using namespace entities;

namespace entities::characters
{
    class Player2 : public Player
    {
    public:
        Player2();
        ~Player2();
        void drawLifeBar();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        void moveX();
    };
}