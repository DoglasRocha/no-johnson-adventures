#include "../../include/managers/graphic_manager.hpp"
#include "../../include/managers/colision_manager.hpp"
#include <iostream>
#include <list>

using namespace sf;
using namespace std;

namespace managers
{
    ColisionManager::ColisionManager() : gravity(1)
    {
        projectilePtr = nullptr;
        player2 = nullptr;
    }

    ColisionManager::Colision ColisionManager::characterColisionWithFloatRect(Character *characterPtr, FloatRect &floatRect)
    {
        Colision colision;

        FloatRect characterBounds = characterPtr->getSprite()->getGlobalBounds(),
                  futureCharacterBounds = characterBounds;

        int deltaX = characterPtr->getVelX(),
            deltaY = characterPtr->getVelY() + characterPtr->getThrust();

        // colisão em Y
        futureCharacterBounds.top += deltaY;

        if (floatRect.intersects(futureCharacterBounds))
        {
            // down
            if (floatRect.top > futureCharacterBounds.top &&
                futureCharacterBounds.top + futureCharacterBounds.height >= floatRect.top)
            {
                colision.down = true;
            }
            // up
            else if (floatRect.top + floatRect.height < futureCharacterBounds.top + futureCharacterBounds.height &&
                     futureCharacterBounds.top <= floatRect.top + floatRect.height)
            {
                colision.up = true;
            }
        }

        // colisão em X
        futureCharacterBounds = characterBounds;
        futureCharacterBounds.left += deltaX;

        if (floatRect.intersects(futureCharacterBounds))
        {
            // right
            if (floatRect.left > futureCharacterBounds.left &&
                futureCharacterBounds.left + futureCharacterBounds.width >= floatRect.left)
            {
                colision.right = true;
            }
            // left
            else if (floatRect.left + floatRect.width < futureCharacterBounds.left + futureCharacterBounds.width &&
                     futureCharacterBounds.left <= floatRect.left + floatRect.width)
            {
                colision.left = true;
            }
        }

        return colision;
    }

    ColisionManager::Colision ColisionManager::characterColisionWithCharacter(Character *characterPtr, Character *character2Ptr)
    {
        Colision colision;

        FloatRect character2Bounds = character2Ptr->getSprite()->getGlobalBounds(),
                  futureCharacter2Bounds = character2Bounds;

        int deltaX = character2Ptr->getVelX(),
            deltaY = character2Ptr->getVelY() + character2Ptr->getThrust();

        futureCharacter2Bounds.top += deltaY, futureCharacter2Bounds.left += deltaX;
        return this->characterColisionWithFloatRect(characterPtr, futureCharacter2Bounds);
    }

    void ColisionManager::runEnemyColision(Enemy *enemyPtr)
    {
        if (!enemyPtr->getAlive())
            return;

        Colision result = runObstacleColisions(enemyPtr);

        if (!result.left && !result.right)
            enemyPtr->moveX();
        else
            enemyPtr->collideX();

        if (!result.up && !result.down)
            enemyPtr->moveY(),
                applyGravity(enemyPtr);
        else
            enemyPtr->collideY();
    }

    ColisionManager *
    ColisionManager::getInstance()
    {
        if (instance == nullptr)
            instance = new ColisionManager();

        return instance;
    }

    void ColisionManager::deleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    ColisionManager *ColisionManager::addEnemy(Enemy *enemyPtr)
    {
        enemyVector.push_back(enemyPtr);
        return instance;
    }

    ColisionManager *ColisionManager::addObstacle(Obstacle *obstaclePtr)
    {
        obstacleList.push_back(obstaclePtr);
        obstaclePtr->setThrust(-(gravity));
        return instance;
    }

    ColisionManager::~ColisionManager()
    {
    }

    void ColisionManager::applyGravity(Entity *entity)
    {
        entity->setVelY(entity->getVelY() + gravity + entity->getThrust());
        entity->setThrust(entity->getThrust() + gravity);
    }

    void ColisionManager::run()
    {
        // enemies
        for (int i = 0, l = enemyVector.size(); i < l; i++)
        {
            runEnemyColision(enemyVector[i]);
        }

        // obstacles
        for (list<Obstacle *>::iterator it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            applyGravity(*it);
        }

        // player
        runPlayerColisions(player);
        runPlayerColisions(player2);
        if (projectilePtr)
            runProjectileColisionWithEntity();
    }

    void ColisionManager::runPlayerColisions(Player *playerPtr)
    {
        if (!playerPtr)
            return;
        Colision colisionSum, c;
        moveX = moveY = true;
        colisionSum = runPlayerColisionWithEnemy(playerPtr);
        c = runObstacleColisions(playerPtr);

        colisionSum.up = colisionSum.up || c.up;
        colisionSum.down = colisionSum.down || c.down;
        colisionSum.left = colisionSum.left || c.left;
        colisionSum.right = colisionSum.right || c.right;

        if (!colisionSum.left && !colisionSum.right)
            playerPtr->moveX();
        else
            playerPtr->collideX();

        if (!colisionSum.up && !colisionSum.down)
            playerPtr->moveY(),
                applyGravity(playerPtr);
        else
            playerPtr->collideY();
    }

    ColisionManager::Colision ColisionManager::runObstacleColisions(Character *characterPtr)
    {
        Colision colisionsSum;

        std::list<Obstacle *>::iterator it;
        for (it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            FloatRect obstacleBounds = (*it)->getShape()->getGlobalBounds();

            Colision colisions = characterColisionWithFloatRect(characterPtr, obstacleBounds);

            if (colisions.down || colisions.up || colisions.left || colisions.right)
            {
                if ((*it)->getIsSolid())
                {
                    colisionsSum.up = colisionsSum.up || colisions.up;
                    colisionsSum.down = colisionsSum.down || colisions.down;
                    colisionsSum.left = colisionsSum.left || colisions.left;
                    colisionsSum.right = colisionsSum.right || colisions.right;
                }
                else
                {
                    (*it)->interact(characterPtr);
                }
            }
        }

        // showHitbox(
        //     futureBoundsCharacter.left,
        //     futureBoundsCharacter.top,
        //     futureBoundsCharacter.width,
        //     futureBoundsCharacter.height);

        return colisionsSum;
    }

    void ColisionManager::showHitbox(int x, int y, int width, int height)
    {
        RectangleShape shape(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::White);

        GraphicManager::getInstance()->drawElement(shape);
    }

    void ColisionManager::setPlayer(Player *playerPtr)
    {
        player = playerPtr;
    }

    void ColisionManager::setPlayer2(Player *player2Ptr)
    {
        player2 = player2Ptr;
    }

    void ColisionManager::setProjectile(Projectile *projectilePtr)
    {
        this->projectilePtr = projectilePtr;
    }

    vector<Enemy *> ColisionManager::getEnemyVector()
    {
        return enemyVector;
    }

    ColisionManager::Colision ColisionManager::runPlayerColisionWithEnemy(Player *playerPtr)
    {
        Colision colisionsSum;

        vector<Enemy *>::iterator it;
        for (int i = 0, l = enemyVector.size(); i < l; i++)
        {
            if (!enemyVector[i]->getAlive())
            {
                playerPtr->addScore(enemyVector[i]->getPoints());
                it = enemyVector.begin() + i;
                enemyVector.erase(it);
            }

            Colision result = characterColisionWithCharacter(playerPtr, enemyVector[i]);

            // colide em X
            if (result.left || result.right)
            {
                result.left ? playerPtr->pushX(-1) : playerPtr->pushX(1);
                playerPtr->sufferAttack(enemyVector[i]);
            }

            // colide em Y
            if (result.up || result.down)
            {
                playerPtr->pushY(result.down),
                    enemyVector[i]->sufferAttack(playerPtr);
            }

            colisionsSum.up = colisionsSum.up || result.up;
            colisionsSum.down = colisionsSum.down || result.down;
            colisionsSum.left = colisionsSum.left || result.left;
            colisionsSum.right = colisionsSum.right || result.right;
        }

        return colisionsSum;
    }

    void ColisionManager::runProjectileColisionWithEntity()
    {
        projectilePtr->setVelY(gravity * 2);
        FloatRect projectileBounds = projectilePtr->getSprite()->getGlobalBounds();
        int deltaX = projectilePtr->getVelX(),
            deltaY = projectilePtr->getVelY() + projectilePtr->getThrust();

        FloatRect playerBounds = player->getSprite()->getGlobalBounds();

        if (projectileBounds.intersects(playerBounds) && player->getAlive())
        {
            if (playerBounds.left < projectileBounds.left)
                player->pushX(-1);
            else
                player->pushX(1);
            projectilePtr->reset();

            player->sufferAttack(projectilePtr->getAttack());
        }

        if (player2)
        {
            FloatRect playerBounds2 = player2->getSprite()->getGlobalBounds();
            if (projectileBounds.intersects(playerBounds2))
            {
                if (playerBounds2.left < projectileBounds.left)
                    player2->pushX(-1);
                else
                    player2->pushX(1);
                projectilePtr->reset();

                player2->sufferAttack(projectilePtr->getAttack());
            }
        }

        projectilePtr->moveX();
        projectilePtr->moveY();

        std::list<Obstacle *>::iterator it;
        for (it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            FloatRect obstacleBounds = (*it)->getShape()->getGlobalBounds();
            if (obstacleBounds.intersects(projectileBounds))
                projectilePtr->reset();
        }
    }

    void ColisionManager::clearLists()
    {
        enemyVector.clear();
        obstacleList.clear();
    }

    void ColisionManager::deleteProjectile()
    {
        // delete ptrProjetil; Por alguma razão que só Deus sabe, isso crasha o jogo.
        // = nullptr;
    }
}