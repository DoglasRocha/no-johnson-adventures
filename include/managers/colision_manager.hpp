#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/characters/enemies/enemy.hpp"
#include "../entities/obstacles/obstacle.hpp"
#include "../entities/characters/character.hpp"
// #include "../entities/projetil.hpp"

#include <vector>
#include <list>

using namespace sf;
using namespace entities::characters;
using namespace entities::obstacles;

namespace managers
{
    class ColisionManager
    {
    private:
        static ColisionManager *instance;
        const int gravity;
        Player *player;
        // Jogador *jogador2;
        // Projetil *ptrProjetil;
        std::vector<Enemy *> enemyVector;
        std::list<Obstacle *> obstacleList;

        ColisionManager();
        bool moveX, moveY;
        int direction;

    public:
        ~ColisionManager();
        static ColisionManager *getInstance();
        static void deleteInstance();
        ColisionManager *addEnemy(Enemy *enemyPtr);
        ColisionManager *addObstacle(Obstacle *obstaclePtr);
        void applyGravity(Entity *entity);
        void run();
        std::vector<Enemy *> getEnemyVector();
        void runPlayerColisions(Player *playerPtr);
        void showHitbox(int x, int y, int width, int height);
        void setPlayer(Player *playerPtr);
        // void setJogador2(Jogador *ptrJogador);
        // void setProjetil(Projetil *ptrProjetil_);
        void runObstacleColisions(Character *characterPtr);
        void runPlayerColisionWithEnemy(Player *playerPtr);
        // void executaColisaoProjetilComEntidade();
        void clearLists();
        // void deletaProjetil();
    };
}
