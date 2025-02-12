#pragma once
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities::obstacles
{
    class Bush : public Obstacle
    {
    private:
        float height;

    public:
        Bush(const int x, const int y);
        ~Bush();
        void interact(Character *playerPtr);
        float getHeight() const;
    };
}
