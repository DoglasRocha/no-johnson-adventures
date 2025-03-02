#pragma once
#include "../utils/ente.hpp"
#include "../managers/graphic_manager.hpp"
#include "../managers/event_handler.hpp"
#include "background_manager.hpp"
#include "button.hpp"
#include "../utils/state.hpp"
#include <memory>

using namespace managers;

struct PlayerInfo
{
    string name;
    int score;
};

class Ranking : public Ente, public State
{
private:
    EventHandler *eventHandler;
    std::shared_ptr<BackgroundManager> background;
    std::vector<PlayerInfo> rankingList;
    Game *gamePtr;
    Font font;
    String playerInput;
    Text inputText, gameOverText;
    NOP::SharedRule rl1, rl2, rl3;
    NOP::SharedCondition c1;

public:
    Ranking(EventHandler *eventHandler = nullptr, Game *gamePtr = nullptr);
    ~Ranking();
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
    void changeState(int option = 0);
    void readFile();
    void writeFile(int points);
    void drawPlayers();
};