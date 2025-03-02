#include "../../../../include/entities/characters/players/player2.hpp"

using namespace entities::characters;

Player2::Player2()
{
    loadTextures("sprites/bigsmoke/bigsmokemoto", 0, 0);
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
    lifeBarText.setString("2P");
}

Player2::~Player2()
{
}

void Player2::drawLifeBar()
{
    RectangleShape bar(Vector2f(lives * 2, 25));
    RectangleShape barBackground(Vector2f(200, 25));

    bar.setFillColor(Color::Green);
    barBackground.setFillColor(Color::Red);

    Vector2f viewPosition = ptrGM->getCenterView();
    bar.setPosition(viewPosition.x + 450, viewPosition.y - 450);
    barBackground.setPosition(viewPosition.x + 450, viewPosition.y - 450);
    bar.setSize(Vector2f(lives * 2, 25));

    lifeBarText.setPosition(viewPosition.x + 660, viewPosition.y - 450);

    ptrGM->drawElement(barBackground);
    ptrGM->drawElement(bar);
    ptrGM->drawElement(lifeBarText);
}

void Player2::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Left);
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
    CEXP(atKeyPressed == sf::Keyboard::Key::Right);
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
    CEXP(atKeyPressed == sf::Keyboard::Key::Up);
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
    CEXP(atKeyReleased == sf::Keyboard::Key::Left);
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
    CEXP(atKeyReleased == sf::Keyboard::Key::Right);
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

void Player2::moveX()
{
    sprite.move((float)velX, 0);
    x += velX;

    // ????
    if (velX == 50 || velX == -50)
    {
        velX = 0;
    }
}