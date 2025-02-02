#include "../../../../include/entities/characters/enemies/enemy.hpp"
#include "../../../../include/entities/characters/character.hpp"

using namespace entities::characters;

Enemy::Enemy() : points(0), attackTick(sf::seconds(1.0f)) {}

Enemy::Enemy(const float attackTick) : points(0), attackTick(sf::seconds(attackTick)) {}

Enemy::~Enemy() {}

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