#include "../../../include/entities/obstacles/fire.hpp"

namespace entities::obstacles
{

    Fire::Fire(const int x, const int y) : Obstacle(45, 70, x, y)
    {
        isSolid = false;
        strength = ((float)rand() / (RAND_MAX * 1.5)) + 1;
        xSize = 45;
        ySize = 70 * strength;

        texture->loadFromFile("../assets/fire/fire1.png");
        shape->setTexture(texture.get());
        shape->setPosition(x, y - ySize);
    }
    Fire::~Fire()
    {
    }
    void Fire::interact(Character *playerPtr)
    {
        playerPtr->burn();
    }
    float Fire::getStrength() const
    {
        return strength;
    }
}