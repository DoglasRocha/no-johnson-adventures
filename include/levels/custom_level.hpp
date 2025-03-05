#pragma once
#include <string>
#include "level.hpp"

using levels::Level;
using std::string;

class CustomLevel : public Level
{
private:
    string path = "";
    Font font;
    String playerInput;
    Text inputText, pathText;
    NOP::SharedRule rl1, rl2, rl3, rl4;
    NOP::SharedCondition c1;

public:
    CustomLevel(ColisionManager *colisionManager = nullptr,
                EventHandler *eventHandler = nullptr,
                Player *playerPtr = nullptr,
                Game *gamePtr = nullptr,
                Player *player2Ptr = nullptr);
    ~CustomLevel();
    void run();
    void changeState(int option = 0);
    void createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY);
    void setupEventHandling(
        NOP::SharedAttribute<sf::Event::EventType> &atEventType,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY);
};