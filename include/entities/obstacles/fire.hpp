#pragma once
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities::obstacles
{
    class Fire : public Obstacle
    {
    private:
        float strength;

    public:
        Fire(const int x, const int y);
        ~Fire();
        void interact(Character *playerPtr);
        float getStrength() const;
    };
}
