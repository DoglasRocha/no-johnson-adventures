#include "../../../../include/entities/characters/enemies/enemy.hpp"
#include "../../../../include/entities/characters/character.hpp"

using namespace entities::characters;

Enemy::Enemy() : points(0), attackTick(sf::seconds(1.0f)) {}

Enemy::Enemy(const float attackTick) : points(0), attackTick(sf::milliseconds(attackTick)) {}

Enemy::~Enemy() {}

void Enemy::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY) {}

void Enemy::slowness()
{
}

void Enemy::burn()
{
}

int Enemy::getPoints()
{
    return points;
}