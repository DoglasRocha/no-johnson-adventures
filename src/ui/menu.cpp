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

    Button *newButton = new Button(250, "../assets/menu/button_level_1.png");
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);

    newButton = new Button(400, "../assets/menu/button_level_2.png");
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);

    newButton = new Button(550, "../assets/menu/button_custom_level.png");
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);

    newButton = new Button(700, "../assets/menu/ranking_button.png");
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);

    newButton = new Button(850, "../assets/menu/exit_button.png");
    buttonList.push_back(newButton);
    eventHandler->subscribe(newButton);

    setupRules();
}

Menu::~Menu()
{
    for (int i = 0; i < buttonList.size(); i++)
    {
        delete buttonList[i];
    }

    rl1->SetCondition(c1);
    rl2->SetCondition(c1);
    rl3->SetCondition(c1);
}

void Menu::run()
{
    draw();
    eventHandler->handleEvents();
}

void Menu::setupEventHandling(
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
    CEXP(atKeyPressed == sf::Keyboard::Key::Down);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->operator++();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl2);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Up);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->operator--();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl3);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Key::Return);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            atKeyPressed->SetValue(sf::Keyboard::Key::Unknown);
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
    this->resetButtons();

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
    cont = cont < 5 ? cont + 1 : 1;
}

void Menu::operator--()
{
    cont = cont > 1 ? cont - 1 : 5;
}

void Menu::changeState(int option)
{
    atNewState->SetValue(option);
}

void Menu::setupRules()
{
    RULE();
    LCONDITION();
    CEXP(atNewState == 1);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::PlayerMenuState, 1);))
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == 2);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::PlayerMenuState, 2);))
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == 3);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::PlayerMenuState, 3);))
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == 4);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::RankingState, 0);))
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewState == 5);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            ptrGM->closeWindow();))
    END_ACTION;
    END_RULE;
}