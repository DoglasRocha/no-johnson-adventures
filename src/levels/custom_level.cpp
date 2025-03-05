#include "../../include/levels/level.hpp"
#include "../../include/game.hpp"

#include "../../include/levels/custom_level.hpp"

CustomLevel::CustomLevel(ColisionManager *colisionManager,
                         EventHandler *eventHandler,
                         Player *playerPtr,
                         Game *gamePtr,
                         Player *player2Ptr)
    : Level(colisionManager, eventHandler, playerPtr, gamePtr, player2Ptr)
{
    background = std::make_shared<BackgroundManager>("medieval_castle/background.png");
    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::White);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOutlineThickness(10);
    inputText.setPosition(Vector2f(100, 500));

    pathText.setFont(font);
    pathText.setCharacterSize(30);
    pathText.setFillColor(sf::Color::White);
    pathText.setOutlineColor(sf::Color::Black);
    pathText.setOutlineThickness(10);
    pathText.setPosition(Vector2f(50, 400));
    pathText.setString("Digite o caminho para o arquivo JSON de descricao de fase:");
}

CustomLevel::~CustomLevel()
{
    rl1->SetCondition(c1);
    rl2->SetCondition(c1);
    rl3->SetCondition(c1);
    rl4->SetCondition(c1);

    std::cout << "destrutor custom level" << std::endl;
}

void CustomLevel::run()
{
    background->draw();
    if (path == "")
    {
        ptrGM->drawElement(pathText);
        ptrGM->drawElement(inputText);
        eventHandler->handleEvents();
    }
    else
    {
        draw();
        eventHandler->handleEvents();
        changeState();
    }
}

void CustomLevel::changeState(int option)
{
    std::cout << "changeState" << std::endl;
    if (!player1Ptr->getAlive())
    {
        gamePtr->changeState(Game::States::RankingState, 0);
    }
    else if (colisionManager->getEnemyVector().empty())
    {
        std::cout << "ranking" << std::endl;
        gamePtr->changeState(Game::States::RankingState, 0);
    }
    std::cout << "changeState" << std::endl;
}

void CustomLevel::createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY)
{
}

void CustomLevel::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{

    RULE(&rl2);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Return);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            changeState();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl1);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Escape);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            changeState();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl3);
    LCONDITION();
    CEXP(atEventType == sf::Event::TextEntered);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(playerInput += eventHandler->getEvent().text.unicode;
               inputText.setString(playerInput);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl4);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::BackSpace);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(playerInput = playerInput.substring(0, playerInput.getSize() - 1);
               inputText.setString(playerInput);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}