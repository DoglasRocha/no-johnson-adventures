#pragma once
#include "enemy.hpp"

using namespace sf;

namespace entities::characters
{
    class Minotaur : public Enemy
    {
    private:
        int hornWear;

    public:
        Minotaur();
        Minotaur(const int x, const int y);
        ~Minotaur();
        void collideX();
        int getAttack();
        void slowness();
        void burn();
    };
}
