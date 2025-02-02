#include "../include/game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

using namespace managers;

GraphicManager *GraphicManager::instance = nullptr;
EventHandler *EventHandler::instance = nullptr;
ColisionManager *ColisionManager::instance = nullptr;
GraphicManager *Ente::ptrGM = nullptr;

Game::
    Game() : graphicManager(GraphicManager::getInstance()),
             eventHandler(EventHandler::getInstance()),
             colisionManager(ColisionManager::getInstance()),
             wall(32, 500, 0, 450),
             wall1(32, 500, 1368, 450),
             platform(1500, 50, 0, 950)
{
    Ente::setGraphicManager(graphicManager);
    CJ.setGraphicManager(graphicManager);
    eventHandler->setGraphicManager(graphicManager);
    eventHandler->subscribe(&CJ);
    colisionManager->addEnemy(&bigNose)->addObstacle(&wall)->addObstacle(&wall1)->addObstacle(&platform)->setPlayer(&CJ);

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        eventHandler->handleEvents();
        colisionManager->run();
        CJ.draw();
        bigNose.draw();
        wall.draw();
        wall1.draw();
        platform.draw();
        graphicManager->showElements();
    }
}

Game::
    ~Game()
{
}
