#include "../include/game.hpp"
#include "../include/levels/level1.hpp"
#include "../include/levels/level2.hpp"

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
             colisionManager(ColisionManager::getInstance())
{
    srand(time(NULL));
    Ente::setGraphicManager(graphicManager);
    eventHandler->setGraphicManager(graphicManager);
    CJ.setGraphicManager(graphicManager);

    eventHandler->subscribe(&CJ);
    eventHandler->subscribe(&BigSmoke);

    colisionManager->setPlayer(&CJ);
    colisionManager->setPlayer2(&BigSmoke);

    currentState = new Level2(colisionManager.get(), eventHandler.get(), &CJ, this, &BigSmoke);

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        currentState->run();
        graphicManager->showElements();
    }
}

Game::
    ~Game()
{
    EventHandler::deleteInstance();
    ColisionManager::deleteInstance();
    GraphicManager::deleteInstance();
    delete formerState;
    delete currentState;
}

int Game::getScore()
{
    return CJ.getScore();
}

void Game::resetScore()
{
    CJ.resetScore();
}

void Game::goToLevel1(int coop)
{
    CJ.reset();

    colisionManager->clearLists();
    if (formerState)
    {
        delete formerState;
        formerState = nullptr;
    }
    formerState = currentState;

    if (coop)
        currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this);

    else
        currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this);
}

void Game::goToLevel2(int coop)
{
    CJ.reset();

    colisionManager->clearLists();
    // if (formerState)
    // {
    //     delete formerState;
    //     formerState = nullptr;
    // }
    // formerState = currentState;

    // if (coop)
    // {
    //     currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this);
    // }
}

void Game::goToRanking(int param)
{
}

void Game::goToMenu(int param)
{
}

void Game::goToPlayerMenu(int level)
{
}