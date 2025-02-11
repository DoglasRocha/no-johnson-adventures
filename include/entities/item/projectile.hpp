#pragma once
#include "item.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities
{
    class Projectile : public Item
    {
    public:
        Projectile(std::string kind, std::string texturePath, characters::Character *owner);
        ~Projectile();
        void setThrust(int thrust);
        void collideX();
        void collideY();
        void reset();
        void moveX();
        void moveY();
        void interact(characters::Character *character);
    };
}
