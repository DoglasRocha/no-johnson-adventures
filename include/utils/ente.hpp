#pragma once
#include "managers/graphic_manager.hpp"
#include <memory>
#include <libnop/framework.h>

using namespace managers;

class Ente : NOP::FBE
{
protected:
    int id;
    static GraphicManager *ptrGM;

public:
    Ente();
    virtual ~Ente();
    virtual void run();
    virtual void draw() = 0;
    static void setGraphicManager(std::shared_ptr<GraphicManager> ptrGM_);
    virtual void setupEventHandling(
        NOP::SharedAttribute<sf::Event::EventType> &atEventType,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY) = 0;
};