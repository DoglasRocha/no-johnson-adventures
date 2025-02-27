#pragma once
#include "managers/graphic_manager.hpp"
#include "managers/event_handler.hpp"
#include "managers/colision_manager.hpp"
#include "entities/characters/players/player1.hpp"
#include "entities/characters/players/player2.hpp"
#include "utils/state.hpp"
#include <memory>
#include <libnop/framework.h>

using namespace managers;
using namespace entities::characters;
using namespace entities::obstacles;

class Game
{
private:
    std::shared_ptr<GraphicManager> graphicManager;
    std::shared_ptr<EventHandler> eventHandler;
    std::shared_ptr<ColisionManager> colisionManager;
    Player1 CJ;
    Player2 BigSmoke;
    State *formerState, *currentState;

public:
    enum States
    {
        Level1State,
        Level2State,
        RankingState,
        MenuState,
        PlayerMenuState,
        Exit
    };
    Game();
    ~Game();
    int getScore();
    void resetScore();
    void goToLevel1(int coop);
    void goToLevel2(int coop);
    void goToRanking();
    void goToMenu();
    void goToPlayerMenu(int level);
    void changeState(States state, int param);
};