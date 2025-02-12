#include "../../include/levels/level.hpp"
#include "../../include/game.hpp"
#include "../../include/entities/obstacles/platform.hpp"
#include "../../include/entities/obstacles/wall.hpp"
#include "../../include/entities/obstacles/bush.hpp"
#include "../../include/entities/obstacles/fire.hpp"
#include "../../include/entities/characters/enemies/big_nose.hpp"
#include "../../include/entities/characters/enemies/bat.hpp"

namespace levels
{
    Level::Level(ColisionManager *colisionManager, EventHandler *eventHandler, Player *playerPtr, Game *gamePtr)
        : colisionManager(colisionManager), eventHandler(eventHandler), player1Ptr(playerPtr), State(gamePtr)
    {
        entityList.append(player1Ptr);
    }

    Level::~Level()
    {
        colisionManager->clearLists();
        entityList.clearList();
    }

    void Level::run()
    {
        handle_colisions();
        eventHandler->handleEvents();
        draw();
        changeState();
    }

    void Level::setupEventHandling(
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY)
    {
    }

    void Level::draw()
    {
        background->draw();
        entityList.drawEntities();
        player1Ptr->drawLifeBar();
    }

    void Level::handle_colisions()
    {
        colisionManager->run();
    }

    void Level::createPlatform(int xSize, int ySize, int posX, int posY)
    {
        Platform *newPlatform = new Platform(xSize, ySize, posX, posY);
        if (newPlatform)
            entityList.append(newPlatform),
                colisionManager->addObstacle(newPlatform);
    }

    void Level::createWall(int ySize, int posX, int posY)
    {
        Wall *newWall = new Wall(32, ySize, posX, posY);
        if (newWall)
            entityList.append(newWall),
                colisionManager->addObstacle(newWall);
    }

    void Level::createBigNose(int posX, int posY)
    {
        BigNose *newNose = new BigNose(posX, posY - 50);
        if (newNose)
            entityList.append(newNose),
                colisionManager->addEnemy(newNose);
    }

    void Level::createBush(int posX, int posY)
    {
        Bush *newBush = new Bush(posX, posY);
        if (newBush)
            entityList.append(newBush),
                colisionManager->addObstacle(newBush);
    }

    void Level::createFire(int posX, int posY)
    {
        Fire *newFire = new Fire(posX, posY);
        if (newFire)
            entityList.append(newFire),
                colisionManager->addObstacle(newFire);
    }

    void Level::createBat(int posX, int posY)
    {
        Bat *newBat = new Bat(posX, posY - 50);
        if (newBat)
            entityList.append(newBat),
                colisionManager->addEnemy(newBat);
    }

    void Level::createMinotaur(int posX, int posY)
    {
        Minotaur *newMinotaur = new Minotaur(posX, posY - 50);
        if (newMinotaur)
            entityList.append(newMinotaur),
                colisionManager->addEnemy(newMinotaur),
                createProjectile(newMinotaur);
    }

    void Level::createProjectile(entities::characters::Minotaur *minotaurPtr)
    {
        Projectile *newProjectile = new Projectile(minotaurPtr);
        if (newProjectile)
            entityList.append(newProjectile),
                colisionManager->setProjectile(newProjectile);
    }
}