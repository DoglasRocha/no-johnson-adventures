#pragma once
#include "../character.hpp"
#include <SFML/Graphics.hpp>
#include "../../../lists/circular.hpp"

using namespace sf;

namespace entities::characters
{
    class Enemy : public Character
    {
    protected:
        int points;
        Clock attackClock;
        const sf::Time attackTick;

    public:
        Enemy();
        Enemy(const float attackTick);
        virtual ~Enemy();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        virtual void collideX() = 0;
        void slowness();
        void burn();
        int getPoints();
        virtual int getBaseLives() = 0;
    };
}
