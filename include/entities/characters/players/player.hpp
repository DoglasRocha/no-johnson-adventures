#pragma once
#include "../character.hpp"
#include "../../item/shield.hpp"
#include "../../item/melee.hpp"
#include <SFML/Graphics.hpp>

using entities::characters::Character;
using namespace sf;

namespace entities::characters
{
    class Player : public Character
    {
    private:
        int score = 0;

    protected:
        std::shared_ptr<Shield> shield;
        std::shared_ptr<Melee> melee;
        Text lifeBarText;
        Font font;

    public:
        Player();
        virtual ~Player();
        virtual void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY) = 0;
        virtual void collideX();
        virtual void moveX();
        void pushX(const int direction);
        void pushY(bool up);
        void slowness();
        void burn();
        void reset();
        virtual void drawLifeBar() = 0;
        void resetScore();
        int getScore();
        void addScore(int score);
        int getBaseLives();
        Shield *getShield();
        Melee *getMelee();
    };
}
