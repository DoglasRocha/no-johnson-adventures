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
        player2 = nullptr;
        neutralizedEnemy = nullptr;
    }

    ColisionManager::Colision ColisionManager::entityColisionWithFloatRect(Entity *entityPtr, FloatRect &floatRect)
    {
        Colision colision;

        FloatRect entityBounds = entityPtr->getGlobalBounds(),
                  futureEntityBounds = entityBounds;

        int deltaX = entityPtr->getVelX(),
            deltaY = entityPtr->getVelY() + entityPtr->getThrust();

        // colisão em Y
        futureEntityBounds.top += deltaY;

        if (floatRect.intersects(futureEntityBounds))
        {
            // down
            if (floatRect.top > futureEntityBounds.top &&
                futureEntityBounds.top + futureEntityBounds.height >= floatRect.top)
            {
                colision.down = true;
            }
            // up
            else if (floatRect.top + floatRect.height < futureEntityBounds.top + futureEntityBounds.height &&
                     futureEntityBounds.top <= floatRect.top + floatRect.height)
            {
                colision.up = true;
            }
        }

        // colisão em X
        futureEntityBounds = entityBounds;
        futureEntityBounds.left += deltaX;

        if (floatRect.intersects(futureEntityBounds))
        {
            // right
            if (floatRect.left > futureEntityBounds.left &&
                futureEntityBounds.left + futureEntityBounds.width >= floatRect.left)
            {
                colision.right = true;
            }
            // left
            else if (floatRect.left + floatRect.width < futureEntityBounds.left + futureEntityBounds.width &&
                     futureEntityBounds.left <= floatRect.left + floatRect.width)
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
        return this->entityColisionWithFloatRect(characterPtr, futureCharacter2Bounds);
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

        // items
        for (int i = 0, l = itemVector.size(); i < l; i++)
            runItemColisionWithEntity(itemVector[i]);
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

            Colision colisions = entityColisionWithFloatRect(characterPtr, obstacleBounds);

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

    void ColisionManager::addItem(Item *itemPtr)
    {
        this->itemVector.push_back(itemPtr);
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
                neutralizedEnemy = enemyVector[i];
                playerPtr->addScore(enemyVector[i]->getPoints());
                it = enemyVector.begin() + i;
                enemyVector.erase(it);
            }

            Colision result = characterColisionWithCharacter(playerPtr, enemyVector[i]);

            // colide em X
            if (result.left || result.right)
            {
                result.left ? playerPtr->pushX(1) : playerPtr->pushX(-1);
                playerPtr->sufferAttack(enemyVector[i]);
            }

            // colide em Y
            if (result.up || result.down && (!result.left && !result.right))
            {
                playerPtr->pushY(result.down),
                    enemyVector[i]->sufferAttack(playerPtr);
            }

            colisionsSum.up = colisionsSum.up || result.up;
            colisionsSum.down = colisionsSum.down || result.down;
            // colisionsSum.left = colisionsSum.left || result.left;
            // colisionsSum.right = colisionsSum.right || result.right;
        }

        return colisionsSum;
    }

    void ColisionManager::runItemColisionWithEntity(Item *itemPtr)
    {
        if (itemPtr->isProjectile())
        {
            runProjectileColision(dynamic_cast<Projectile *>(itemPtr));
        }
        else if (itemPtr->isConsumable())
        {
            runPotionColision(dynamic_cast<Potion *>(itemPtr));
        }
        else if (itemPtr->isShield())
        {
            runShieldOrMeleeColision(dynamic_cast<Shield *>(itemPtr));
        }
        else if (itemPtr->isMelee())
        {
            runShieldOrMeleeColision(dynamic_cast<Melee *>(itemPtr));
        }
    }

    void ColisionManager::clearLists()
    {
        enemyVector.clear();
        obstacleList.clear();
        itemVector.clear();
        neutralizedEnemy = nullptr;
    }

    void ColisionManager::deleteProjectile()
    {
        // delete ptrProjetil; Por alguma razão que só Deus sabe, isso crasha o jogo.
        // = nullptr;
    }

    Enemy *ColisionManager::getNeutralizedEnemy()
    {
        Enemy *temp = neutralizedEnemy;
        neutralizedEnemy = nullptr;
        return temp;
    }

    void ColisionManager::runProjectileColision(Projectile *projectilePtr)
    {
        applyGravity(projectilePtr);
        FloatRect projectileBounds = projectilePtr->getSprite()->getGlobalBounds();

        Colision colisionWithPlayer1 = entityColisionWithFloatRect(player, projectileBounds);
        if (colisionWithPlayer1.down || colisionWithPlayer1.up || colisionWithPlayer1.left || colisionWithPlayer1.right)
        {
            if (colisionWithPlayer1.right)
                player->pushX(-1);
            else
                player->pushX(1);
            projectilePtr->reset();

            player->sufferAttack(projectilePtr->getAttack());
        }

        if (player2)
        {
            Colision ColisionWithPlayer2 = entityColisionWithFloatRect(player2, projectileBounds);
            if (ColisionWithPlayer2.down || ColisionWithPlayer2.up || ColisionWithPlayer2.left || ColisionWithPlayer2.right)
            {
                if (ColisionWithPlayer2.right)
                    player2->pushX(-1);
                else
                    player2->pushX(1);
                projectilePtr->reset();

                player2->sufferAttack(projectilePtr->getAttack());
            }
        }

        std::list<Obstacle *>::iterator it;
        for (it = obstacleList.begin(); it != obstacleList.end(); it++)
        {
            if (!(*it)->getIsSolid())
                continue;
            FloatRect obstacleBounds = (*it)->getShape()->getGlobalBounds();
            Colision colisionWithObstacle = entityColisionWithFloatRect(projectilePtr, obstacleBounds);
            if (colisionWithObstacle.down || colisionWithObstacle.up || colisionWithObstacle.left || colisionWithObstacle.right)
                projectilePtr->reset();
        }

        projectilePtr->moveX();
        projectilePtr->moveY();
    }

    void ColisionManager::runPotionColision(Potion *potionPtr)
    {
        FloatRect itemBounds = potionPtr->getGlobalBounds();
        Colision colisionWithPlayer1 = entityColisionWithFloatRect(player, itemBounds);
        if (colisionWithPlayer1.down || colisionWithPlayer1.up || colisionWithPlayer1.left || colisionWithPlayer1.right)
        {
            potionPtr->interact(player);
            itemVector.erase(std::find(itemVector.begin(), itemVector.end(), potionPtr));
        }

        if (player2)
        {
            Colision ColisionWithPlayer2 = entityColisionWithFloatRect(player2, itemBounds);
            if (ColisionWithPlayer2.down || ColisionWithPlayer2.up || ColisionWithPlayer2.left || ColisionWithPlayer2.right)
            {
                potionPtr->interact(player2);
                itemVector.erase(std::find(itemVector.begin(), itemVector.end(), potionPtr));
            }
        }

        Colision colisionSum;

        // colisão com obstaculo
        for (auto &obstacle : obstacleList)
        {
            FloatRect obstacleBounds = obstacle->getShape()->getGlobalBounds();

            Colision colision = entityColisionWithFloatRect(potionPtr, obstacleBounds);
            colisionSum.up = colisionSum.up || colision.up;
            colisionSum.down = colisionSum.down || colision.down;
            colisionSum.left = colisionSum.left || colision.left;
            colisionSum.right = colisionSum.right || colision.right;
        }

        if (!colisionSum.left && !colisionSum.right)
            potionPtr->moveX();
        else
            potionPtr->collideX();

        if (!colisionSum.up && !colisionSum.down)
            potionPtr->moveY(), applyGravity(potionPtr);
        else
        {
            potionPtr->collideY();
        }
    }

    void ColisionManager::runShieldOrMeleeColision(Shield *shieldPtr)
    {
        if (!shieldPtr->getIsActive())
            return;

        // colision with enemies
        for (auto &enemy : enemyVector)
        {
            FloatRect shieldBounds = shieldPtr->getGlobalBounds();
            Colision colisionWithEnemy = entityColisionWithFloatRect(enemy, shieldBounds);
            if (colisionWithEnemy.down || colisionWithEnemy.up || colisionWithEnemy.left || colisionWithEnemy.right)
            {
                shieldPtr->interact(enemy);
            }
        }

        shieldPtr->moveX();
        shieldPtr->moveY();
    }

    void ColisionManager::runShieldOrMeleeColision(Melee *meleePtr)
    {
        if (!meleePtr->getIsActive())
            return;

        // colision with enemies
        for (auto &enemy : enemyVector)
        {
            FloatRect shieldBounds = meleePtr->getGlobalBounds();
            Colision colisionWithEnemy = entityColisionWithFloatRect(enemy, shieldBounds);
            if (colisionWithEnemy.down || colisionWithEnemy.up || colisionWithEnemy.left || colisionWithEnemy.right)
            {
                meleePtr->interact(enemy);
            }
        }

        meleePtr->moveX();
        meleePtr->moveY();
    }
}