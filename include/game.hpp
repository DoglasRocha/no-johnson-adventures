#pragma once
#include "managers/graphic_manager.hpp"
#include "managers/event_handler.hpp"
#include "entities/characters/players/player1.hpp"
#include "entities/characters/enemies/big_nose.hpp"
#include "entities/obstacles/wall.hpp"
#include "entities/obstacles/platform.hpp"
#include <memory>
// #include <libnop/fbe.h>
#include <libnop/framework.h>

using namespace managers;
using namespace entities::characters;
using namespace entities::obstacles;

class Game : NOP::FBE
{
private:
    std::shared_ptr<GraphicManager> graphicManager;
    std::shared_ptr<EventHandler> eventHandler;
    Player1 CJ;
    BigNose bigNose;
    Wall wall, wall1;
    Platform platform;

public:
    Game();
    ~Game();
};