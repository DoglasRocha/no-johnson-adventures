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

bool EventHandler::getEvent()
{
    return (*ptrGM.lock()).getWindow()->pollEvent(this->event);
}

void EventHandler::setPlayer(Ente *player)
{
    this->player = player;
}

void EventHandler::subscribe(Ente *ente)
{
    ente->setupEventHandling(
        this->atKeyPressed, this->atKeyReleased,
        this->atMouseButtonPressed, this->atMouseButtonReleased,
        this->atMousePositionX, this->atMousePositionY);
}

void EventHandler::handleEvents()
{
    while (this->getEvent())
    {
        this->atEventType->SetValue(this->event.type);
    }
}