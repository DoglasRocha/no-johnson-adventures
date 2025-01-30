#include "../../include/entities/entity.hpp"

namespace entities
{
    Entity::Entity() : x(0), y(0), velX(0), velY(0), thrust(0) {}

    Entity::~Entity() {}

    void Entity::run()
    {
    }

    int Entity::getThrust() const
    {
        return thrust;
    }

    int Entity::getX() const
    {
        return x;
    }

    int Entity::getY() const
    {
        return y;
    }

    void Entity::setX(const int x)
    {
        this->x = x;
    }

    void Entity::setY(const int y)
    {
        this->y = y;
    }

    void Entity::setVelX(const int vel)
    {
        this->velX = vel;
    }

    void Entity::setVelY(const int vel)
    {
        this->velY = vel;
    }

    int Entity::getVelX() const
    {
        return velX;
    }

    int Entity::getVelY() const
    {
        return velY;
    }
}