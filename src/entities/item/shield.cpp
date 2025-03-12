#include "../../../include/entities/item/shield.hpp"
#include "../../../include/entities/item/shield.hpp"

namespace entities
{
    Shield::Shield(characters::Character *owner) : Item("shield", "../assets/shield.png")
    {
        shouldDraw = false;
        this->attack = 0;
        this->owner = owner;

        scaleSprite(0.8, 0.8);
        setOriginToCenter();

        this->x = owner->getX();
        this->y = owner->getY();
        this->sprite->setPosition(this->x, this->y);
    }

    Shield::~Shield()
    {
    }

    void Shield::setThrust(int thrust)
    {
    }

    void Shield::collideX()
    {
    }

    void Shield::collideY()
    {
    }

    void Shield::reset()
    {
    }

    void Shield::moveX()
    {
        int offset = direction == "left" ? -60 : 60;
        this->x = this->owner->getX() + offset;
        this->sprite->setPosition(this->x, this->y);
    }

    void Shield::moveY()
    {
        this->y = this->owner->getY();
        this->sprite->setPosition(this->x, this->y);
    }

    void Shield::interact(characters::Character *character)
    {
        character->collideX();
        character->collideY();
    }

    void Shield::activate(std::string direction)
    {
        shouldDraw = true;
        this->direction = direction;
        isActive = true;
    }

    void Shield::deactivate()
    {
        shouldDraw = false;
        isActive = false;
    }

    bool Shield::getIsActive()
    {
        return isActive;
    }
}
