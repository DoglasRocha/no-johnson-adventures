#include "../../include/ui/button.hpp"

Button::Button() : xSize(350),
                   ySize(150),
                   x(0),
                   y(0),
                   shape(make_shared<RectangleShape>(Vector2f(xSize, ySize))),
                   texture(make_shared<Texture>()),
                   param(0),
                   action(nullptr)
{
}

Button::Button(const int y, const string texturePath, void *action(int), int param) : Button()
{
    this->action = action;
    this->param = param;
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
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    RULE();
    LCONDITION();
    CEXP(atMousePositionX >= this->x)
    AND CEXP(atMousePositionX <= this->x + this->xSize)
        AND CEXP(atMousePositionY >= this->y)
            AND CEXP(atMousePositionY <= this->y + this->ySize);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->action(this->param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}

void Button::draw()
{
    ptrGM->drawElement(*shape);
}