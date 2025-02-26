#pragma once
#include "../utils/ente.hpp"
#include "../game.hpp"
#include <string>
#include <memory>
using namespace std;
using namespace sf;

class Button : public Ente
{
private:
    const int xSize, ySize, x;
    int y, param;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Texture> texture;
    Game *gamePtr;
    Game::States state;

public:
    Button();
    Button(const int y, const string texturePath, Game *gamePtr, Game::States state, int param);
    ~Button();
    void run();
    void setupEventHandling(
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY);
    void draw();
    Shape *getShape();
};