#include "../../../../include/entities/characters/players/player.hpp"

using namespace entities::characters;
using namespace entities;

Player::Player() : Character()
{
    this->lives = 100;
    this->attack = 20;

    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");
    shield = std::make_shared<Shield>(this);
    melee = std::make_shared<Melee>(this);
}

Player::~Player()
{
}

void Player::collideX()
{
    this->velX = 0;
}

void Player::moveX()
{
    sprite.move((float)velX, 0);
    x += velX;
    ptrGM->centerWindow(x);

    // ????
    if (velX == 50 || velX == -50)
    {
        velX = 0;
    }
}

void Player::pushX(const int direction)
{
    if (direction < 0)
    {
        velX = -50;
    }
    else
    {
        velX = 50;
    }
}

void Player::pushY(bool up)
{
    thrust = up ? -6 : 6;
}

void Player::slowness()
{
    velX *= 0.75;
}

void Player::burn()
{
    lives--;
    if (this->direction == "LEFT")
    {
        velX = -9;
    }
    else
    {
        velX = 9;
    }
}

void Player::reset()
{
    lives = 100;
    x = 700;
    y = 500;
    alive = true;
    sprite.setPosition(x, y);
    ptrGM->centerWindow(x);
}

void Player::resetScore()
{
    score = 0;
}

int Player::getScore()
{
    return score;
}

void Player::addScore(int score)
{
    this->score += score;
}

int Player::getBaseLives()
{
    return 100;
}

Shield *Player::getShield()
{
    return shield.get();
}

Melee *Player::getMelee()
{
    return melee.get();
}