#include "../../include/managers/event_handler.hpp"

using managers::EventHandler;

EventHandler::EventHandler()
{
    ptrGM = nullptr;
}

EventHandler::~EventHandler()
{
}

bool EventHandler::getEvent(sf::Event &event)
{
    return ptrGM->getWindow()->pollEvent(event);
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

void EventHandler::setGraphicManager(managers::GraphicManager *ptrGM)
{
    this->ptrGM = ptrGM;
}