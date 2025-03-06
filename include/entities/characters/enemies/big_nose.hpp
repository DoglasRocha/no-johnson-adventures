#pragma once
#include "enemy.hpp"

using namespace sf;

namespace entities::characters
{
    class BigNose : public Enemy
    {
    private:
        int sneezePower;

    public:
        BigNose();
        BigNose(const int x, const int y);
        ~BigNose();
        void collideX();
        int getAttack();
        void slowness();
        void burn();
        int getBaseLives();
    };
}
