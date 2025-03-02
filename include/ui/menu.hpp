#pragma once
#include "../utils/ente.hpp"
#include "../managers/graphic_manager.hpp"
#include "../managers/event_handler.hpp"
#include "background_manager.hpp"
#include "button.hpp"
#include "../utils/state.hpp"
#include <memory>

using namespace managers;

class Menu : public Ente, public State
{
private:
    int cont = 1;
    EventHandler *eventHandler;
    std::shared_ptr<BackgroundManager> background;
    std::vector<Button *> buttonList;
    Game *gamePtr;
    Text title;
    Font font;
    NOP::SharedRule rl1, rl2, rl3;
    NOP::SharedCondition c1;

public:
    Menu(EventHandler *eventHandler = nullptr, Game *gamePtr = nullptr);
    ~Menu();
    void run();
    void setupEventHandling(
        NOP::SharedAttribute<sf::Event::EventType> &atEventType,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY);
    void draw();
    void resetButtons();
    void operator++();
    void operator--();
    void changeState(int option = 0);
};