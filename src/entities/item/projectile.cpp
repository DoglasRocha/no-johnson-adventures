#include "../../../include/entities/item/projectile.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using entities::characters::Character;

namespace entities
{

    Projectile::Projectile(characters::Character *owner) : Item("projectile", "../assets/bullet.png")
    {
        this->owner = owner;
        attack = 10;

        setupRules();
        reset();
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::setThrust(int thrust)
    {
        // this->thrust = thrust;
    }

    void Projectile::collideX()
    {
        reset();
    }

    void Projectile::collideY()
    {
        reset();
    }

    void Projectile::reset()
    {
        velX = velY = 0;
        atElapsedTime->SetValue(attackClock.getElapsedTime());
    }

    void Projectile::moveX()
    {
        sprite->move(velX, 0);
        x += velX;
    }

    void Projectile::moveY()
    {
        sprite->move(0, velY);
        y += velY;
    }

    void Projectile::interact(characters::Character *character)
    {
        character->sufferAttack(this->attack);
        reset();
        atForceReset->SetValue(true);
    }

    void Projectile::setupRules()
    {

        RULE();
        LCONDITION();
        CEXP(atElapsedTime >= atResetTick)
        OR
            CEXP(atForceReset == true);
        END_CONDITION;
        ACTION();
        INSTIGATE(
            METHOD(
                execReset();))
        END_ACTION;
        END_CONDITION;
        END_RULE;
    }

    void Projectile::execReset()
    {
        if (!owner->getAlive())
            return;

        direction = owner->getDirection();

        if (direction == "left")
        {
            x = owner->getX();
            velX = -12;
        }
        else
        {
            x = owner->getX() + 100;
            velX = 12;
        }

        y = owner->getY();
        sprite->setPosition(x, y);
        velY = 0;

        attackClock.restart();
        atElapsedTime->SetValue(sf::Time::Zero);
        atForceReset->SetValue(false);
        atResetTick->SetValue(sf::milliseconds(rand() % 2000 + 1000));
    }
}
