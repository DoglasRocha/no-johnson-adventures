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
             formerState(nullptr), currentState(nullptr), param(-1)
{
    srand(time(NULL));
    Ente::setGraphicManager(graphicManager);
    eventHandler->setGraphicManager(graphicManager);
    CJ.setGraphicManager(graphicManager);

    eventHandler->subscribe(&CJ);
    eventHandler->subscribe(&BigSmoke);

    colisionManager->setPlayer(&CJ);
    colisionManager->setPlayer2(&BigSmoke);

    setupRules();
    this->changeState(States::MenuState, 0);

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

void Game::goToCustomLevel(int coop)
{
    CustomLevel *customLevel = new CustomLevel(colisionManager.get(), eventHandler.get(), &CJ, this, coop ? &BigSmoke : nullptr);
    currentState = customLevel;
    eventHandler->subscribe(customLevel);
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

    this->param = param;
    atNewState->SetValue(state);

    if (formerState != nullptr)
    {
        delete formerState;
        formerState = nullptr;
    }
}

void Game::setupRules()
{
    RULE();
    LCONDITION();
    CEXP(atNewState == States::MenuState);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToMenu();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::Level1State);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToLevel1(param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::Level2State);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToLevel2(param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::CustomLevelState);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToCustomLevel(param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::RankingState);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToRanking();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::PlayerMenuState);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->goToPlayerMenu(param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == States::Exit);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            graphicManager->closeWindow();))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}