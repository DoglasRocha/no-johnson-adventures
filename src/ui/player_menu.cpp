#include "../include/ui/player_menu.hpp"

PlayerMenu::PlayerMenu(EventHandler *eventHandler, Game *gamePtr, int level)
    : eventHandler(eventHandler), gamePtr(gamePtr)
{
    atNewLevel->SetValue(level);
    background = std::make_shared<BackgroundManager>("menu/background.png");

    buttonList.push_back(new Button(425, "../assets/menu/button_1_player.png"));
    eventHandler->subscribe(buttonList.back());

    buttonList.push_back(new Button(600, "../assets/menu/button_2_players.png"));
    eventHandler->subscribe(buttonList.back());

    setupRules();
}

PlayerMenu::~PlayerMenu()
{
    for (auto button : buttonList)
    {
        delete button;
    }

    rl1->SetCondition(c1);
    rl2->SetCondition(c1);
    rl3->SetCondition(c1);
}

void PlayerMenu::run()
{
    draw();
    eventHandler->handleEvents();
}

void PlayerMenu::setupEventHandling(
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

void PlayerMenu::draw()
{
    background->draw();

    this->resetButtons();
    buttonList[cont - 1]->getShape()->setOutlineThickness(10);
    for (auto button : buttonList)
    {
        button->draw();
    }
}

void PlayerMenu::resetButtons()
{
    for (auto button : buttonList)
    {
        button->getShape()->setOutlineThickness(0);
    }
}

void PlayerMenu::operator++()
{
    cont = cont < 2 ? cont + 1 : 1;
}

void PlayerMenu::operator--()
{
    cont = cont > 1 ? cont - 1 : 2;
}

void PlayerMenu::changeState(int option)
{
    atCoop->SetValue(option);
}

void PlayerMenu::setupRules()
{
    RULE();
    LCONDITION();
    CEXP(atNewLevel == 1)
    AND CEXP(atCoop == 1);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::Level1State, 0);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewLevel == 2)
    AND CEXP(atCoop == 1);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::Level2State, 0);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewLevel == 3)
    AND CEXP(atCoop == 1);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::CustomLevelState, 0);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewLevel == 1)
    AND CEXP(atCoop == 2);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::Level1State, 1);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewLevel == 2)
    AND CEXP(atCoop == 2);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::Level2State, 1);))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atNewLevel == 3)
    AND CEXP(atCoop == 2);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            gamePtr->changeState(Game::States::CustomLevelState, 1);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}