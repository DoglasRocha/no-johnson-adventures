#pragma once
#include "player.hpp"

using namespace entities;

class Game;

namespace entities::characters
{
    class TestPlayer : public Player
    {
    private:
        Game *gamePtr;

    public:
        TestPlayer(Game *gamePtr);
        ~TestPlayer();
        void drawLifeBar();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        void collideX();
    };
}