#include "../include/game.hpp"
#include <thread>
#include <chrono>
#include <iostream>

using namespace managers;

GraphicManager *GraphicManager::instance = nullptr;

Game::
    Game() : player({100, 100}),
             graphicManager(GraphicManager::getInstance())
{
    player.setFillColor(sf::Color::Blue);
    player.setPosition({500, 500});

    RULE();
    LCONDITION();
    CEXP(eventType == sf::Event::Closed);
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(graphicManager->closeWindow();));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(eventType == sf::Event::KeyPressed)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        keyPressed->SetValue(event.key.code);));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(keyPressed == sf::Keyboard::Left)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        player.move(-10.f, 0.f);
        keyPressed->SetValue(sf::Keyboard::A);));
    END_ACTION;
    END_RULE;

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        graphicManager->drawElement(player);
        while (graphicManager->getWindow()->pollEvent(event))
        {
            eventType->SetValue(event.type);
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(20));
        graphicManager->showElements();
    }
}

Game::
    ~Game()
{
}

void Game::movePlayer(int x, int y)
{
}
