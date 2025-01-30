#include "../../../../include/entities/characters/player1.hpp"

using namespace entities::characters;

Player1::Player1()
{
    sprite = RectangleShape({100, 100});
    sprite.setFillColor(Color::Green);
    x = 700, y = 500;
    sprite.setPosition(x, y);
}

Player1::~Player1()
{
    // Destructor implementation
}

void Player1::setupEventHandling(
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::A);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setDirection("left");
            this->setVelX(-5);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::D);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setDirection("right");
            this->setVelX(5);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::W);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelY(-5);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::S);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelY(5);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::Key::A);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelX(0);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::Key::D);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelX(0);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::Key::W);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelY(0);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::Key::S);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->setVelY(0);))
    END_ACTION;

    END_CONDITION;
    END_RULE;
}