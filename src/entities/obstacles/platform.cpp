#include "../../../include/entities/obstacles/platform.hpp"

namespace entities::obstacles
{

    Platform::Platform(const int sizeX, const int sizeY, const int x, const int y) : Obstacle(sizeX, sizeY, x, y)
    {
        thrust = -1;

        texture->loadFromFile("../assets/background/platform.png");
        texture->setRepeated(true);

        shape->setTexture(texture.get());
        shape->setTextureRect({0, 0, xSize, 24});
    }

    Platform::~Platform()
    {
    }

    void Platform::interact(Character *playerPtr)
    {
    }

}