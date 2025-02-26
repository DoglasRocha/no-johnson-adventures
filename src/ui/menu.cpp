#include "../../include/ui/menu.hpp"
#include "../../include/game.hpp"

Menu::Menu(EventHandler *eventHandler, Game *gamePtr)
    : eventHandler(eventHandler), gamePtr(gamePtr)
{
    background = std::make_shared<BackgroundManager>("menu/background.png");

    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");

    title.setFont(font);
    title.setString("N.O. Johnson Adventures");
    title.setCharacterSize(90);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(10);
    title.setPosition(100, 75);

    Button *newButton = new Button(250, "../assets/menu/button_level_1.png", gamePtr, Game::States::Level1State, 0);
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);
}

Menu::~Menu()
{
    for (int i = 0; i < buttonList.size(); i++)
    {
        delete buttonList[i];
    }
}

void Menu::run()
{
    draw();
    eventHandler->handleEvents();
}

void Menu::setupEventHandling(
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Down);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->operator--();))
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
            this->operator++();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Return);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->changeState(cont);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}

void Menu::draw()
{
    background->draw();
    ptrGM->drawElement(title);

    Button *tmpButton = buttonList[cont - 1];
    tmpButton->getShape()->setOutlineThickness(10);

    for (int i = 0; i < buttonList.size(); i++)
        buttonList[i]->draw();
}

void Menu::resetButtons()
{
    for (int i = 0; i < buttonList.size(); i++)
    {
        buttonList[i]->getShape()->setOutlineThickness(0);
    }
}

void Menu::operator++()
{
    cont = cont < 4 ? cont + 1 : 1;
}

void Menu::operator--()
{
    cont = cont > 1 ? cont - 1 : 4;
}

void Menu::changeState(int option)
{
    switch (option)
    {
    case 1:
        gamePtr->changeState(Game::States::PlayerMenuState, 1);
        break;
    case 2:
        gamePtr->changeState(Game::States::PlayerMenuState, 2);
        break;
    case 3:
        gamePtr->changeState(Game::States::RankingState, 0);
        break;
    case 4:
        ptrGM->closeWindow();
    default:
        break;
    }
}