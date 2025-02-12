#include "../../../include/entities/obstacles/bush.hpp"

namespace entities::obstacles
{

    Bush::Bush(const int x, const int y) : Obstacle(100, 50, x, y)
    {
        isSolid = false;
        height = (float(rand()) / RAND_MAX) + 1;
        xSize = 100;
        ySize = 50 * height;

        shape = std::make_shared<RectangleShape>(Vector2f(xSize, ySize));
        texture->loadFromFile("../assets/pixel_art_forest/PNG/background_layers/bush.png");
        shape->setTexture(texture.get());
        shape->setPosition(x, y - ySize);
    }
    Bush::~Bush()
    {
    }
    void Bush::interact(Character *playerPtr)
    {
        playerPtr->slowness();
    }

    float Bush::getHeight() const
    {
        return height;
    }
}
