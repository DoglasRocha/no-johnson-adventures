#pragma once
#include "item.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities
{
    class Potion : public Item
    {
    public:
        Potion(characters::Character *owner = nullptr);
        ~Potion();
        void setThrust(int thrust);
        void collideX();
        void collideY();
        void reset();
        void moveX();
        void moveY();
        void interact(characters::Character *character);
    };
}
