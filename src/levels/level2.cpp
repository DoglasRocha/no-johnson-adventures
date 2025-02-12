#include "../../include/levels/level2.hpp"
#include "../../include/game.hpp"
#include "../../include/entities/obstacles/platform.hpp"
#include "../../include/entities/obstacles/wall.hpp"
#include "../../include/entities/obstacles/bush.hpp"
#include "../../include/entities/obstacles/fire.hpp"
#include "../../include/entities/characters/enemies/big_nose.hpp"
#include "../../include/entities/characters/enemies/bat.hpp"

Level2::Level2(ColisionManager *colisionManager, EventHandler *eventHandler, Player *playerPtr, Game *gamePtr)
    : Level(colisionManager, eventHandler, playerPtr, gamePtr)
{
    int platformInfo[11][4] = {
        {1000, 50, 32, 950},
        {750, 50, 1000, 800},
        {1750, 50, 1750, 950},
        {200, 20, 400, 300},
        {300, 20, 270, 700},
        {400, 20, 800, 450},
        {500, 20, 1500, 600},
        {500, 20, 1500, 250},
        {400, 20, 2100, 325},
        {450, 20, 2800, 750},
        {350, 20, 2800, 450}};

    int wallInfo[4][3] = {
        {500, 0, 500},
        {200, 1000, 800},
        {200, 1750, 800},
        {500, 3500, 500}};

    for (int i = 0; i < 3; i++)
        createPlatform(
            platformInfo[i][0],
            platformInfo[i][1],
            platformInfo[i][2],
            platformInfo[i][3]);

    for (int i = 3; i < 11; i++)
        createPlatformWithRandomThingsAbove(
            platformInfo[i][0],
            platformInfo[i][1],
            platformInfo[i][2],
            platformInfo[i][3]);

    for (int i = 0; i < 4; i++)
        createWall(
            wallInfo[i][0],
            wallInfo[i][1],
            wallInfo[i][2]);

    createBat(100, 300);
    createBat(1400, 600);
    createBat(3350, 600);
    createMinotaur(2500, 600);

    background = std::make_shared<BackgroundManager>("medieval_castle/background.png");
}

Level2::~Level2()
{
    colisionManager->deleteProjectile();
}

void Level2::changeState(int option)
{
    if (!player1Ptr->getAlive())
    {
        gamePtr->goToRanking();
    }
    else if (colisionManager->getEnemyVector().empty())
    {
        gamePtr->goToRanking();
    }
}

void Level2::createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY)
{
    createPlatform(xSize, ySize, posX, posY);
    if ((bigNoseCount < 3) || (rand() % 2))
    {
        createBigNose(posX + (rand() % (xSize - 100)), posY);
        bigNoseCount++;
    }

    if ((fireCount < 3) || (rand() % 5))
    {
        createFire(posX + (rand() % (xSize - 100)), posY);
        fireCount++;
    }
}