#pragma once
#include "item.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities
{
    class Melee : public Item
    {
    private:
        bool isActive;

    public:
        Melee(characters::Character *owner = nullptr);
        ~Melee();
        void setThrust(int thrust);
        void collideX();
        void collideY();
        void reset();
        void moveX();
        void moveY();
        void interact(characters::Character *character);
        void activate(std::string direction);
        void deactivate();
        bool getIsActive();
    };
}
