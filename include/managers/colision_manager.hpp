#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/characters/enemies/enemy.hpp"
#include "../entities/obstacles/obstacle.hpp"
#include "../entities/characters/character.hpp"
#include "../entities/item/projectile.hpp"
#include "../entities/item/potion.hpp"
#include "../entities/item/item.hpp"

#include <vector>
#include <list>

using namespace sf;
using namespace entities::characters;
using namespace entities::obstacles;
using namespace entities;

namespace managers
{
    class ColisionManager
    {
    private:
        static ColisionManager *instance;
        const int gravity;
        Player *player;
        Player *player2;
        std::vector<Enemy *> enemyVector;
        std::list<Obstacle *> obstacleList;
        std::vector<Item *> itemVector;
        Enemy *neutralizedEnemy;

        ColisionManager();
        bool moveX, moveY;
        int direction;

        struct Colision
        {
            bool up = false,
                 down = false,
                 left = false,
                 right = false;
        };

        Colision entityColisionWithFloatRect(Entity *entityPtr, FloatRect &floatRect);
        Colision characterColisionWithCharacter(Character *characterPtr, Character *character2Ptr);
        void runEnemyColision(Enemy *enemyPtr);

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
        void setPlayer2(Player *player2Ptr);
        void addItem(Item *itemPtr);
        Colision runObstacleColisions(Character *characterPtr);
        Colision runPlayerColisionWithEnemy(Player *playerPtr);
        void runItemColisionWithEntity(Item *itemPtr);
        void clearLists();
        void deleteProjectile();
        Enemy *getNeutralizedEnemy();
        void runProjectileColision(Projectile *projectilePtr);
        void runPotionColision(Potion *potionPtr);
    };
}
