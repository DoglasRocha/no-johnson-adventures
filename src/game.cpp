#include "../include/game.hpp"
#include "../include/ui/menu.hpp"
#include "../include/utils/state.hpp"
#include "../include/levels/level1.hpp"
#include "../include/levels/level2.hpp"
#include "../include/levels/custom_level.hpp"
#include "../include/ui/player_menu.hpp"
#include "../include/ui/ranking.hpp"

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
             colisionManager(ColisionManager::getInstance()),
             formerState(nullptr)
{
    srand(time(NULL));
    Ente::setGraphicManager(graphicManager);
    eventHandler->setGraphicManager(graphicManager);
    CJ.setGraphicManager(graphicManager);

    eventHandler->subscribe(&CJ);
    eventHandler->subscribe(&BigSmoke);

    colisionManager->setPlayer(&CJ);
    colisionManager->setPlayer2(&BigSmoke);

    // Menu *menu = new Menu(eventHandler.get(), this);
    CustomLevel *menu = new CustomLevel(colisionManager.get(), eventHandler.get(), &CJ, this, nullptr, "../config_level.json");
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
    // delete formerState;
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
    currentState = new Level1(colisionManager.get(), eventHandler.get(), &CJ, this, coop ? &BigSmoke : nullptr);
}

void Game::goToLevel2(int coop)
{
    currentState = new Level2(colisionManager.get(), eventHandler.get(), &CJ, this, coop ? &BigSmoke : nullptr);
}

void Game::goToRanking()
{
    Ranking *ranking = new Ranking(eventHandler.get(), this);
    currentState = ranking;
    eventHandler->subscribe(ranking);
}

void Game::goToMenu()
{
    CJ.resetScore();
    BigSmoke.resetScore();

    Menu *menu = new Menu(eventHandler.get(), this);
    currentState = menu;
    eventHandler->subscribe(menu);
}

void Game::goToPlayerMenu(int level)
{
    PlayerMenu *playerMenu = new PlayerMenu(eventHandler.get(), this, level);
    currentState = playerMenu;
    eventHandler->subscribe(playerMenu);
}

void Game::changeState(States state, int param)
{
    CJ.reset();
    BigSmoke.reset();
    colisionManager->clearLists();

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
        this->goToPlayerMenu(param);
        break;

    case States::Exit:
        graphicManager->closeWindow();
        break;
    }
    delete formerState;
    formerState = nullptr;
}