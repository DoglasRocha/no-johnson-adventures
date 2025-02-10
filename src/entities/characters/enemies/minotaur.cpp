#include "../../../../include/entities/characters/enemies/minotaur.hpp"

namespace entities::characters
{
    Minotaur::Minotaur() : Enemy(2000)
    {
        points = 250;
        direction = "right";
        lives = 120;
        attack = 35;
        hornWear = (rand() % 2) + 1;

        loadTextures("sprites/minotaur/minotaur", 0, 4);
        currentNode = textures.begin();
        sprite.setTexture(*currentNode->getData());

        x = y = 400;
        setOriginToCenter();
        scaleSprite(5, 5);
        velX = 3;
    }

    Minotaur::Minotaur(const int x, const int y) : Minotaur()
    {
        this->x = x;
        this->y = y;
        velY = -1;
        sprite.setPosition(x, y);
    }

    Minotaur::~Minotaur()
    {
        // Destructor implementation
    }

    void Minotaur::collideX()
    {
        velX = velX == 3 ? -3 : 3;
        direction = direction == "left" ? "right" : "left";
        scaleSprite(-1, 1);
    }

    int Minotaur::getAttack()
    {
        return attack / hornWear;
    }

    void Minotaur::slowness()
    {
    }

    void Minotaur::burn()
    {
    }
}