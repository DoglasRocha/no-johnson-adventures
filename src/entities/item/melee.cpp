#include "../../../include/entities/item/melee.hpp"

namespace entities
{
    Melee::Melee(characters::Character *owner) : Item("melee", "../assets/flower.png")
    {
        shouldDraw = false;
        isActive = false;
        this->attack = 1;
        this->owner = owner;

        scaleSprite(2, 2);
        setOriginToCenter();

        this->x = owner->getX();
        this->y = owner->getY();
        this->sprite->setPosition(this->x, this->y);
    }

    Melee::~Melee()
    {
    }

    void Melee::setThrust(int thrust)
    {
    }

    void Melee::collideX()
    {
    }

    void Melee::collideY()
    {
    }

    void Melee::reset()
    {
    }

    void Melee::moveX()
    {
        int offset = direction == "left" ? -60 : 60;
        this->x = this->owner->getX() + offset;
        this->sprite->setPosition(this->x, this->y);
    }

    void Melee::moveY()
    {
        this->y = this->owner->getY();
        this->sprite->setPosition(this->x, this->y);
    }

    void Melee::interact(characters::Character *character)
    {
        character->sufferAttack(this->attack);
    }

    void Melee::activate(std::string direction)
    {
        shouldDraw = true;
        this->direction = direction;
        isActive = true;
    }

    void Melee::deactivate()
    {
        shouldDraw = false;
        isActive = false;
    }

    bool Melee::getIsActive()
    {
        return isActive;
    }
}
