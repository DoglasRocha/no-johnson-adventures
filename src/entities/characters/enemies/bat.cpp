#include "../../../../include/entities/characters/enemies/bat.hpp"

namespace entities::characters
{
    Bat::Bat() : Enemy(2000)
    {
        points = 50;
        direction = "left";
        lives = 40;
        attack = 20;
        wingStrength = rand() % 5;
        velY = 1;

        loadTextures("sprites/bat/bat", 0, 3);
        currentNode = textures.begin();
        sprite.setTexture(*(currentNode->getData()));
        x = y = 400;
        setOriginToCenter();
        scaleSprite(3, 3);
    }

    Bat::Bat(const int x, const int y) : Bat()
    {
        this->x = x;
        this->y = y;

        sprite.setPosition(x, y);
    }

    Bat::~Bat()
    {
    }

    void Bat::collideX()
    {
    }

    void Bat::collideY()
    {
        velY = 0;
        thrust = !thrust ? -2 : 0;
    }

    void Bat::moveY()
    {
        if (y < 100)
            velY = 1, thrust = 0;

        animate();
        if (velY >= 8)
            velY = 8;

        sprite.move(0, velY);
        y += velY;
    }

    void Bat::slowness()
    {
    }

    void Bat::burn()
    {
    }

    int Bat::getAttack()
    {
        if (attackClock.getElapsedTime() >= attackTick)
        {
            attackClock.restart();
            return attack + wingStrength;
        }

        return 0;
    }

    void Bat::setThrust(const int thrust)
    {
    }

}