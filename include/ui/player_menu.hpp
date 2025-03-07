#pragma once
#include "../utils/ente.hpp"
#include "../managers/graphic_manager.hpp"
#include "../managers/event_handler.hpp"
#include "background_manager.hpp"
#include "button.hpp"
#include "../utils/state.hpp"
#include <memory>

using namespace managers;

class PlayerMenu : public Ente, public State
{
private:
    int cont = 1, level;
    EventHandler *eventHandler;
    std::shared_ptr<BackgroundManager> background;
    std::vector<Button *> buttonList;
    Game *gamePtr;
    NOP::SharedRule rl1, rl2, rl3;
    NOP::SharedCondition c1;
    NOP::SharedAttribute<int> atNewLevel{NOP::BuildAttribute(-1)};
    NOP::SharedAttribute<int> atCoop{NOP::BuildAttribute(-1)};

public:
    PlayerMenu(EventHandler *eventHandler = nullptr, Game *gamePtr = nullptr, int level = 1);
    ~PlayerMenu();
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
    void setupRules();
};