#pragma once
#include "player.hpp"

using namespace entities;

namespace entities::characters
{
    class Player1 : public Player
    {
    public:
        Player1();
        ~Player1();
        void drawLifeBar();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
    };
}