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
    float velX = 0, velY = 0;

    RULE();
    LCONDITION();
    CEXP(atEventType == sf::Event::Closed);
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(graphicManager->closeWindow();));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atEventType == sf::Event::KeyPressed)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        atKeyPressed->SetValue(event.key.code);));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atEventType == sf::Event::KeyReleased)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        atKeyReleased->SetValue(event.key.code);));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::A)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velX = -1;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::D)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velX = 1;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::W)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velY = -1;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::S)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velY = 1;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::A)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velX = 0;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::D)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velX = 0;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::W)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velY = 0;));
    END_ACTION;
    END_RULE;

    RULE();
    LCONDITION();
    CEXP(atKeyReleased == sf::Keyboard::S)
    END_CONDITION;
    ACTION();
    INSTIGATE(METHOD(
        velY = 0;));
    END_ACTION;
    END_RULE;

    while (graphicManager->checkWindowOpen())
    {
        graphicManager->clearWindow();
        player.move(velX, velY);
        graphicManager->drawElement(player);
        while (graphicManager->getWindow()->pollEvent(event))
        {
            atEventType->SetValue(event.type);
            // rlKeyPressed->Notify();
            // rlKeyReleased->Notify();
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
