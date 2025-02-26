#include "../include/game.hpp"
#include "../include/ui/menu.hpp"
#include "../include/utils/state.hpp"
#include "../include/levels/level1.hpp"
#include "../include/levels/level2.hpp"

#include <thread>
#include <chrono>
#include <iostream>

using namespace managers;
using namespace levels;

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

    Menu *menu = new Menu(eventHandler.get(), this);
    currentState = menu;
    eventHandler->subscribe(menu);

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
    return CJ.getScore() + BigSmoke.getScore();
}

void Game::resetScore()
{
    CJ.resetScore();
    BigSmoke.resetScore();
}

void Game::goToLevel1(int coop)
{
    if (coop)
        currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this, nullptr);

    else
        currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this, &BigSmoke);
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

void Game::goToRanking()
{
}

void Game::goToMenu()
{
}

void Game::goToPlayerMenu(States state)
{
}

void Game::changeState(States state, int param)
{
    CJ.reset();
    BigSmoke.reset();
    colisionManager->clearLists();

    if (formerState)
    {
        delete formerState;
        formerState = nullptr;
    }
    formerState = currentState;

    switch (state)
    {
    case States::Level1State:
        this->goToLevel1(param);
        break;

    case States::Level2State:
        this->goToLevel2(param);
        break;

    case States::MenuState:
        this->goToMenu();
        break;

    case States::RankingState:
        this->goToRanking();
        break;

    case States::PlayerMenuState:
        this->goToPlayerMenu(state);
        break;
    }
}