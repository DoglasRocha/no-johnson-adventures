#include "../../../include/entities/item/projectile.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities
{

    Projectile::Projectile(std::string kind, std::string texturePath, characters::Character *owner) : Item(kind, texturePath)
    {
        this->owner = owner;
        attack = 10;
        reset();
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::setThrust(int thrust)
    {
        this->thrust = thrust;
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
            x = owner->getX() + 260;
            velX = 12;
        }

        y = owner->getY() + 50;
        sprite->setPosition(x, y);
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
}
