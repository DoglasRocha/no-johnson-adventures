#include "../../../../include/entities/characters/players/player1.hpp"

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

    lifeBarText.setFont(font);
    lifeBarText.setCharacterSize(25);
    lifeBarText.setFillColor(sf::Color::White);
    lifeBarText.setOutlineColor(sf::Color::Black);
    lifeBarText.setOutlineThickness(10);
    lifeBarText.setString("1P");
}

Player1::~Player1()
{
}

void Player1::drawLifeBar()
{
    RectangleShape bar(Vector2f(lives * 2, 25));
    RectangleShape barBackground(Vector2f(200, 25));

    bar.setFillColor(Color::Green);
    barBackground.setFillColor(Color::Red);

    Vector2f viewPosition = ptrGM->getCenterView();
    bar.setPosition(viewPosition.x - 650, viewPosition.y - 450);
    barBackground.setPosition(viewPosition.x - 650, viewPosition.y - 450);
    bar.setSize(Vector2f(lives * 2, 25));

    lifeBarText.setPosition(viewPosition.x - 690, viewPosition.y - 450);

    ptrGM->drawElement(barBackground);
    ptrGM->drawElement(bar);
    ptrGM->drawElement(lifeBarText);
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
            if (jumps < 2) {
                this->thrust = -5;
                jumps++;
            }))
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
}