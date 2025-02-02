#include "../../../../../include/entities/characters/players/player1.hpp"

using namespace entities::characters;

Player1::Player1()
{
    loadTextures("sprites/cj/cjandar", 0, 6);
    currentNode = textures.begin();
    sprite.setTexture(*currentNode->getData());
    x = 700,
    y = 500;
    sprite.setPosition(x, y);
    setOriginToCenter();
    scaleSprite(3.0, 3.0);
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
            if (this->getDirection() == "right") {
                this->setDirection("left");
                sprite.scale(-1.f, 1);
            } this->setVelX(-6);))
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
            if (this->getDirection() == "left") {
                this->setDirection("right");
                sprite.scale(-1.f, 1);
            } this->setDirection("right");
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
            this->setVelX(0);
            resetAnimation();))
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
            this->setVelX(0);
            resetAnimation();))
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