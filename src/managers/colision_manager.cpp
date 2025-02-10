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
        // jogador2 = nullptr;
    }

    ColisionManager *ColisionManager::getInstance()
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
        for (int i = 0, l = enemyVector.size(); i < l; i++)
        {
            moveX = moveY = true;

            if (!enemyVector[i]->getAlive())
                continue;

            runObstacleColisions(enemyVector[i]);

            if (moveX)
                enemyVector[i]->moveX();
            else
                enemyVector[i]->collideX();

            if (moveY)
                enemyVector[i]->moveY(),
                    applyGravity(enemyVector[i]);
            else
                enemyVector[i]->collideY();
        }

        for (list<Obstacle *>::iterator it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            applyGravity(*it);
        }

        runPlayerColisions(player);
        // executarColisoesJogador(jogador2);
        if (projectilePtr)
            runProjectileColisionWithEntity();
    }

    void ColisionManager::runPlayerColisions(Player *playerPtr)
    {
        moveX = moveY = true;
        runPlayerColisionWithEnemy(playerPtr);
        runObstacleColisions(playerPtr);
        if (moveX)
            playerPtr->moveX();
        else
            playerPtr->collideX();

        if (moveY)
            playerPtr->moveY(),
                applyGravity(playerPtr);
        else
            playerPtr->collideY();
    }

    void ColisionManager::runObstacleColisions(Character *characterPtr)
    {

        FloatRect boundsCurrentCharacter = characterPtr->getSprite()->getGlobalBounds(),
                  futureBoundsCharacter = boundsCurrentCharacter;
        int deltaX = characterPtr->getVelX(),
            deltaY = characterPtr->getVelY() + characterPtr->getThrust();

        // futureBoundsCharacter.top += deltaY, futureBoundsCharacter.left += deltaX;

        std::list<Obstacle *>::iterator it;
        for (it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            FloatRect obstacleBounds = (*it)->getShape()->getGlobalBounds();

            futureBoundsCharacter = boundsCurrentCharacter;
            futureBoundsCharacter.left += deltaX; // ??
            // checa se colide em X
            if (obstacleBounds.intersects(futureBoundsCharacter))
            {
                if ((*it)->getIsSolid())
                    moveX = false;
                else
                {
                    (*it)->interact(characterPtr);
                    characterPtr->checkAlive();
                }
            }

            futureBoundsCharacter = boundsCurrentCharacter;
            futureBoundsCharacter.top += deltaY;
            // checa se colide em Y
            if (obstacleBounds.intersects(futureBoundsCharacter))
            {
                if ((*it)->getIsSolid())
                    moveY = false;
            }
        }

        futureBoundsCharacter.left += deltaX;
        // showHitbox(
        //     futureBoundsCharacter.left,
        //     futureBoundsCharacter.top,
        //     futureBoundsCharacter.width,
        //     futureBoundsCharacter.height);
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

    // void ColisionManager::setJogador2(Player *playerPtr)
    // {
    //     jogador2 = playerPtr;
    // }

    void ColisionManager::setProjectile(Projectile *projectilePtr)
    {
        this->projectilePtr = projectilePtr;
    }

    vector<Enemy *> ColisionManager::getEnemyVector()
    {
        return enemyVector;
    }

    void ColisionManager::runPlayerColisionWithEnemy(Player *playerPtr)
    {

        FloatRect playerBounds = playerPtr->getSprite()->getGlobalBounds(),
                  futurePlayerBounds = playerBounds;
        int deltaX = playerPtr->getVelX(),
            deltaY = playerPtr->getVelY() + playerPtr->getThrust();
        vector<Enemy *>::iterator it;

        futurePlayerBounds.top += deltaY, futurePlayerBounds.left += deltaX;

        for (int i = 0, l = enemyVector.size(); i < l; i++)
        {
            if (!enemyVector[i]->getAlive())
            {
                playerPtr->addScore(enemyVector[i]->getPoints());
                it = enemyVector.begin() + i;
                enemyVector.erase(it);
            }

            FloatRect enemyBounds = enemyVector[i]->getSprite()->getGlobalBounds();

            // colide em X
            futurePlayerBounds = playerBounds;
            futurePlayerBounds.left += deltaX;
            if (enemyBounds.intersects(futurePlayerBounds))
            {
                if (futurePlayerBounds.left < enemyBounds.left)
                    playerPtr->pushX(-1);
                else
                    playerPtr->pushX(1);

                playerPtr->sufferAttack(enemyVector[i]);
            }

            // colide em Y
            futurePlayerBounds = playerBounds;
            futurePlayerBounds.top += deltaY;
            if (enemyBounds.intersects(futurePlayerBounds) &&
                playerBounds.top + playerBounds.height < enemyBounds.top)
                playerPtr->pushY(),
                    moveY = false,
                    enemyVector[i]->sufferAttack(playerPtr);
        }

        futurePlayerBounds.left += deltaX;
        // showHitbox(futurePlayerBounds.left, futurePlayerBounds.top, futurePlayerBounds.width, futurePlayerBounds.height);
    }

    void ColisionManager::runProjectileColisionWithEntity()
    {
        projectilePtr->setVelY(gravity * 2);
        FloatRect projectileBounds = projectilePtr->getSprite()->getGlobalBounds();
        int deltaX = projectilePtr->getVelX(),
            deltaY = projectilePtr->getVelY() + projectilePtr->getThrust();

        FloatRect playerBounds = player->getSprite()->getGlobalBounds();

        if (projectileBounds.intersects(playerBounds))
        {
            if (playerBounds.left < projectileBounds.left)
                player->pushX(-1);
            else
                player->pushX(1);
            projectilePtr->reset();

            player->sufferAttack(projectilePtr->getAttack());
        }

        // if (player2)
        // {
        //     FloatRect playerBounds2 = player2->getSprite()->getGlobalBounds();
        //     if (projectileBounds.intersects(playerBounds2))
        //     {
        //         if (playerBounds2.left < projectileBounds.left)
        //             player2->repelirX(-1);
        //         else
        //             player2->repelirX(1);
        //         projectilePtr->reset();

        //         player2->recebeAtaque(projectilePtr->getAtaque());
        //     }
        // }

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

    // void ColisionManager::deletaProjetil()
    // {
    //     // delete ptrProjetil; Por alguma razão que só Deus sabe, isso crasha o jogo.
    //      = nullptr;
    // }
}