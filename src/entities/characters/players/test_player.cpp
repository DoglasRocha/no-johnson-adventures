#include "../../../../include/entities/characters/players/test_player.hpp"
#include "../../../../include/game.hpp"

using namespace entities::characters;

TestPlayer::TestPlayer(Game *gamePtr) : gamePtr(gamePtr)
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

    velX = 6;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::drawLifeBar()
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

void TestPlayer::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
}

void TestPlayer::collideX()
{
    gamePtr->changeState(Game::States::Exit, 0);
}