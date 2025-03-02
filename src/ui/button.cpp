#include "../../include/ui/button.hpp"
#include "../../include/game.hpp"

Button::Button() : xSize(350),
                   ySize(150),
                   x(550),
                   y(0),
                   shape(make_shared<RectangleShape>(Vector2f(xSize, ySize))),
                   texture(make_shared<Texture>()),
                   param(0),
                   gamePtr(nullptr)
{
}

Button::Button(const int y, const string texturePath, Game *gamePtr, Game::States state, int param) : Button()
{
    this->state = state;
    this->gamePtr = gamePtr;
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
    rl1->SetCondition(c1);
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
    RULE(&rl1);
    LCONDITION();
    CEXP(atMousePositionX >= this->x)
    AND CEXP(atMousePositionX <= this->x + this->xSize)
        AND CEXP(atMousePositionY >= this->y)
            AND CEXP(atMousePositionY <= this->y + this->ySize);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->gamePtr->changeState(this->state, this->param);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}

void Button::draw()
{
    ptrGM->drawElement(*shape);
}

Shape *Button::getShape()
{
    return shape.get();
}