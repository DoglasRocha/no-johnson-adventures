#include "../../../include/entities/obstacles/obstacle.hpp"

using namespace entities::obstacles;

Obstacle::Obstacle() {}

Obstacle::Obstacle(const int sizeX, const int sizeY)
{
    this->xSize = sizeX;
    this->ySize = sizeY;
    shape = new RectangleShape(Vector2f(sizeX, sizeY));
    texture = new Texture();
}

Obstacle::Obstacle(const int sizeX, const int sizeY, const int x, const int y) : Obstacle(sizeX, sizeY)
{
    this->x = x;
    this->y = y;

    shape->setPosition(x, y);
}

Obstacle::~Obstacle()
{
    if (shape)
    {
        delete shape;
    }
    if (texture)
    {
        delete texture;
    }
}

int Obstacle::getSizeX() const
{
    return xSize;
}

void Obstacle::setSizeX(const int sizeX)
{
    xSize = sizeX;
}

int Obstacle::getSizeY() const
{
    return ySize;
}

void Obstacle::setSizeY(const int sizeY)
{
    ySize = sizeY;
}

Drawable *Obstacle::getDraw()
{
    return shape;
}

Shape *Obstacle::getShape()
{
    return shape;
}

void Obstacle::draw()
{
    ptrGM->drawElement(*shape);
}

bool Obstacle::getIsSolid() const
{
    return isSolid;
}

void Obstacle::setupEventHandling(
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
}

void Obstacle::setThrust(int thrust)
{
}