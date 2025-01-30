#include "../include/game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

using namespace managers;

GraphicManager *GraphicManager::instance = nullptr;
EventHandler *EventHandler::instance = nullptr;
GraphicManager *Ente::ptrGM = nullptr;

Game::
    Game() : graphicManager(GraphicManager::getInstance()),
             eventHandler(EventHandler::getInstance())
{
    Ente::setGraphicManager(graphicManager);
    CJ.setGraphicManager(graphicManager);
    eventHandler->setGraphicManager(graphicManager);
    eventHandler->subscribe(&CJ);

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        eventHandler->handleEvents();
        CJ.moveX();
        CJ.moveY();
        CJ.draw();
        graphicManager->showElements();
    }
}

Game::
    ~Game()
{
}
