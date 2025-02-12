#include "../../../include/entities/obstacles/wall.hpp"

namespace entities::obstacles
{
    Wall::Wall(const int tamX, const int tamY, const int posX, const int posY) : Obstacle(tamX, tamY, posX, posY)
    {
        thrust = -1;

        texture->loadFromFile("../assets/background/wall.png");
        texture->setRepeated(true);

        shape->setTexture(texture.get());
        shape->setTextureRect({0, 0, 32, ySize});
    }

    Wall::~Wall()
    {
    }

    void Wall::interact(Character *playerPtr)
    {
    }
}