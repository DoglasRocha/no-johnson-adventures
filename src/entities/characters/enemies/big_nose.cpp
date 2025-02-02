#include "../../../../include/entities/characters/enemies/big_nose.hpp"

using namespace entities::characters;

BigNose::BigNose() : Enemy(500)
{
    points = 10;
    direction = "left";
    lives = 20;
    attack = 5;
    sneezePower = rand() % 5;

    loadTextures("sprites/big_nose/big_nose", 1, 3);
    currentNode = textures.begin();
    sprite.setTexture(*currentNode->getData());
    x = y = 200;
    setOriginToCenter();
    scaleSprite(.25, .25);
    velX = -1;
}

BigNose::BigNose(const int x, const int y) : BigNose()
{
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
}

void BigNose::setupEventHandling(
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
}

BigNose::~BigNose()
{
}

void BigNose::collideX()
{
    velX = velX == 1 ? -1 : 1;
    direction = direction == "left" ? "right" : "left";
    scaleSprite(-1, 1);
}

int BigNose::getAttack()
{
    if (attackClock.getElapsedTime() >= attackTick)
    {
        attackClock.restart();
        return attack + sneezePower;
    }
    return 0;
}

void BigNose::slowness()
{
}

void BigNose::burn()
{
}