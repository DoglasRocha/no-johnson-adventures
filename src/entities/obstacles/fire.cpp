#include "../../../include/entities/obstacles/fire.hpp"
#include <sstream>

namespace entities::obstacles
{

    Fire::Fire(const int x, const int y) : Obstacle(45, 70, x, y)
    {
        isSolid = false;
        strength = ((float)rand() / (RAND_MAX * 1.5)) + 1;
        xSize = 45;
        ySize = 70 * strength;

        shape = std::make_shared<RectangleShape>(Vector2f(xSize, ySize));
        std::stringstream buffer;
        buffer << "../assets/fire/fire" << (rand() % 8) + 1 << ".png";
        texture->loadFromFile(buffer.str());
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