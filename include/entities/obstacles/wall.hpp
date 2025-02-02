#pragma once
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

namespace entities::obstacles
{
    class Wall : public Obstacle
    {
    public:
        Wall(const int tamX, const int tamY, const int posX, const int posY);
        ~Wall();
        void interact(Character *playerPtr);
    };
}