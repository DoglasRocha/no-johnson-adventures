#include "../../include/ui/button.hpp"
#include "../../include/game.hpp"

Button::Button() : xSize(350),
                   ySize(125),
                   x(550),
                   y(0),
                   shape(make_shared<RectangleShape>(Vector2f(xSize, ySize))),
                   texture(make_shared<Texture>())
{
}

Button::Button(const int y, const string texturePath) : Button()
{
    this->y = y;
    if (!texture->loadFromFile(texturePath))
    {
        throw runtime_error("Failed to load texture");
    }
    shape->setTexture(texture.get());
    shape->setOutlineColor(Color::White);
    shape->setPosition(x, y);
}

Button::~Button()
{
}

void Button::run()
{
}

void Button::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
}

void Button::draw()
{
    ptrGM->drawElement(*shape);
}

Shape *Button::getShape()
{
    return shape.get();
}