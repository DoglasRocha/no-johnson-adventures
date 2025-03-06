#include "../../../include/entities/item/potion.hpp"

namespace entities
{
    Potion::Potion(characters::Character *owner) : Item("consumable", "../assets/potion.png")
    {
        this->attack = -(rand() % owner->getBaseLives() + 1);
        this->owner = nullptr;

        scaleSprite(0.075, 0.075);
        setOriginToCenter();

        this->x = owner->getX();
        this->y = owner->getY();
        this->sprite->setPosition(this->x, this->y);
    }

    Potion::~Potion()
    {
    }

    void Potion::setThrust(int thrust)
    {
        // this->thrust = thrust;
    }

    void Potion::collideX()
    {
        this->velX = 0;
    }

    void Potion::collideY()
    {
        this->velY = 0;
    }

    void Potion::reset()
    {
    }

    void Potion::moveX()
    {
        this->x += this->velX;
        this->sprite->move(this->velX, 0);
    }

    void Potion::moveY()
    {
        this->y += this->velY;
        this->sprite->move(0, this->velY);
    }

    void Potion::interact(characters::Character *character)
    {
        character->sufferAttack(this->attack);
        this->shouldDraw = false;
    }
}