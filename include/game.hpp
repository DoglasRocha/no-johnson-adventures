#pragma once
#include "managers/graphic_manager.hpp"
#include "managers/event_handler.hpp"
#include "entities/characters/player1.hpp"
#include <memory>
// #include <libnop/fbe.h>
#include <libnop/framework.h>

using namespace managers;
using namespace entities::characters;

class Game : NOP::FBE
{
private:
    std::shared_ptr<GraphicManager> graphicManager;
    std::shared_ptr<EventHandler> eventHandler;
    Player1 CJ;

public:
    Game();
    ~Game();
};