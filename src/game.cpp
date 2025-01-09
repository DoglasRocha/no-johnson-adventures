#include "../include/game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

using namespace managers;

GraphicManager *GraphicManager::instance = nullptr;
EventHandler *EventHandler::instance = nullptr;

Game::
    Game() : graphicManager(GraphicManager::getInstance()),
             eventHandler(EventHandler::getInstance())
{
    eventHandler->setGraphicManager(graphicManager);

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        eventHandler->handleEvents();
        graphicManager->showElements();
    }
}

Game::
    ~Game()
{
}
