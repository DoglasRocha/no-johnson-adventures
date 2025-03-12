#pragma once
#include "item.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities
{
    class Projectile : public Item
    {
    private:
        NOP::SharedAttribute<sf::Time> atResetTick{NOP::BuildAttribute(sf::Time::Zero)};
        NOP::SharedAttribute<sf::Time> atElapsedTime{NOP::BuildAttribute(sf::Time::Zero)};
        NOP::SharedAttribute<bool> atForceReset{NOP::BuildAttribute(false)};
        sf::Clock attackClock;

    public:
        Projectile(characters::Character *owner);
        ~Projectile();
        void setThrust(int thrust);
        void collideX();
        void collideY();
        void reset();
        void moveX();
        void moveY();
        void interact(characters::Character *character);
        void setupRules();
        void execReset();
    };
}
