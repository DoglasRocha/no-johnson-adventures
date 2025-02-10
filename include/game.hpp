#pragma once
#include "managers/graphic_manager.hpp"
#include "managers/event_handler.hpp"
#include "managers/colision_manager.hpp"
#include "entities/characters/players/player1.hpp"
#include "entities/characters/enemies/big_nose.hpp"
#include "entities/characters/enemies/minotaur.hpp"
#include "entities/item/projectile.hpp"
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
    std::shared_ptr<ColisionManager> colisionManager;
    Player1 CJ;
    BigNose bigNose;
    Minotaur minotaur;
    Projectile projectile;
    Wall wall, wall1;
    Platform platform;

public:
    Game();
    ~Game();
};