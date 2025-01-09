#pragma once
#include "managers/graphic_manager.hpp"
#include "managers/event_handler.hpp"
#include <memory>
// #include <libnop/fbe.h>
#include <libnop/framework.h>

using namespace managers;

class Game : NOP::FBE
{
private:
    std::shared_ptr<GraphicManager> graphicManager;
    std::shared_ptr<EventHandler> eventHandler;

public:
    Game();
    ~Game();
};