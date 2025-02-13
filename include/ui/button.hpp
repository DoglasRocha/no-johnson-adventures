#pragma once
#include "../utils/ente.hpp"
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
    void *action;

public:
    Button();
    Button(const int y, const string texturePath, void *action(int), int param);
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
};