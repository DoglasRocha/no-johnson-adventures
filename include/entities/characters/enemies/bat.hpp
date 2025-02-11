#pragma once
#include "enemy.hpp"

using namespace sf;

namespace entities::characters
{
    class Bat : public Enemy
    {
    private:
        int wingStrength;

    public:
        Bat();
        Bat(const int x, const int y);
        ~Bat();
        void collideX();
        void collideY();
        void moveY();
        void slowness();
        void burn();
        int getAttack();
        void setThrust(const int thrust);
    };
}