#include "../../include/managers/event_handler.hpp"

using managers::EventHandler;

EventHandler::EventHandler()
{
    // setup basic events
    RULE();
    LCONDITION();
    CEXP(this->atEventType == sf::Event::EventType::Closed);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            (*ptrGM.lock()).closeWindow();))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(this->atEventType == sf::Event::EventType::KeyPressed);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->atKeyPressed->SetValue(this->event.key.code, true);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(this->atEventType == sf::Event::EventType::KeyReleased);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->atKeyReleased->SetValue(this->event.key.code, true);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(this->atEventType == sf::Event::EventType::MouseButtonPressed);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->atMouseButtonPressed->SetValue(this->event.mouseButton.button, true);
            this->atMousePositionX->SetValue(this->event.mouseButton.x, true);
            this->atMousePositionY->SetValue(this->event.mouseButton.y, true);))
    END_ACTION;

    END_CONDITION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(this->atEventType == sf::Event::EventType::MouseButtonReleased);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            this->atMouseButtonReleased->SetValue(this->event.mouseButton.button, true);))
    END_ACTION;

    END_CONDITION;
    END_RULE;
}

EventHandler::~EventHandler()
{
}

EventHandler *EventHandler::getInstance()
{
    if (instance == nullptr)
        instance = new EventHandler();

    return instance;
}

void EventHandler::deleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void EventHandler::setGraphicManager(std::shared_ptr<GraphicManager> ptrGM)
{
    this->ptrGM = ptrGM;
}

bool EventHandler::pollEvent()
{
    return (*ptrGM.lock()).getWindow()->pollEvent(this->event);
}

sf::Event EventHandler::getEvent()
{
    return this->event;
}

void EventHandler::setPlayer(Ente *player)
{
    this->player = player;
}

void EventHandler::subscribe(Ente *ente)
{
    ente->setupEventHandling(
        this->atEventType, this->atKeyPressed, this->atKeyReleased,
        this->atMouseButtonPressed, this->atMouseButtonReleased,
        this->atMousePositionX, this->atMousePositionY);
}

void EventHandler::handleEvents()
{
    while (this->pollEvent())
    {
        this->atEventType->SetValue(this->event.type, true);
    }
}