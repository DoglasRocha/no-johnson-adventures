#include "../../../include/entities/characters/character.hpp"
#include <sstream>

using namespace entities::characters;

Character::Character() : lives(0), jumps(0), attack(0), alive(true), direction("right"), animationTick(sf::milliseconds(125))
{
}

Character::~Character() {}

void Character::moveX()
{
    sprite.move((float)velX, 0);
    x += velX;
}

void Character::moveY()
{
    sprite.move(0, (float)velY);
    y += velY;
}

void Character::setJumps(const int jumps)
{
    this->jumps = jumps;
}

int Character::getJumps() const
{
    return jumps;
}

Drawable *Character::getDraw()
{
    return &sprite;
}

Sprite *Character::getSprite()
{
    return &sprite;
}

std::string Character::getDirection() const
{
    return direction;
}

void Character::setDirection(const std::string direction)
{
    this->direction = direction;
}

void Character::setOriginToCenter()
{
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    sprite.setPosition(x + bounds.width / 2, y + bounds.height / 2);
}

void Character::setThrust(const int thrust)
{
    if (this->thrust < 0)
    {
        this->thrust = thrust;
    }
}

void Character::draw()
{
    if (!this->alive)
        return;

    ptrGM->drawElement(sprite);
    if (this->velX != 0)
        this->animate();
}

void Character::collideY()
{
    this->velY = 0;
    this->jumps = 0;
}

int Character::getAttack()
{
    return attack;
}

void Character::sufferAttack(Character *character)
{
    if (!this->alive)
        return;

    lives -= character->getAttack();
    checkAlive();
}

void Character::sufferAttack(int damage)
{
    lives -= damage;
    checkAlive();
}

void Character::checkAlive()
{
    if (lives <= 0)
    {
        lives = 0;
        alive = false;
    }
}

bool Character::getAlive() const
{
    return alive;
}

void Character::loadTextures(const std::string path, const int start, const int end)
{
    Texture *texture;

    for (int i = start; i <= end; i++)
    {
        std::stringstream buffer;
        buffer << "../assets/" << path << i << ".png";
        texture = new Texture();
        if (!texture->loadFromFile(buffer.str()))
        {
            std::cerr << "Error loading texture" << std::endl;
            exit(1);
        }
        else
            this->textures.append(texture);
    }
}

void Character::scaleSprite(const float xFactor, const float yFactor)
{
    sprite.setScale(xFactor, yFactor);
    FloatRect bounds = sprite.getGlobalBounds();
    x = bounds.left;
    y = bounds.top;
}

void Character::animate()
{
    if (animationClock.getElapsedTime() > animationTick)
    {
        currentNode = currentNode->getNext();
        sprite.setTexture(*currentNode->getData());
        animationClock.restart();
    }
}

void Character::resetAnimation()
{
    currentNode = textures.begin();
    sprite.setTexture(*currentNode->getData());
}
