#pragma once
#include "managers/graphic_manager.hpp"
#include <memory>
// #include <libnop/fbe.h>
#include <libnop/framework.h>

using namespace managers;

class Game : NOP::FBE
{
private:
    std::shared_ptr<GraphicManager> graphicManager;
    sf::Event event;
    NOP::SharedAttribute<sf::Event::EventType> atEventType{
        NOP::BuildAttribute(sf::Event::EventType::GainedFocus)};
    NOP::SharedAttribute<sf::Keyboard::Key> atKeyPressed{
        NOP::BuildAttribute(sf::Keyboard::Escape)};
    NOP::SharedAttribute<sf::Keyboard::Key> atKeyReleased{
        NOP::BuildAttribute(sf::Keyboard::Escape)};
    sf::RectangleShape player;

    NOP::SharedRule rlKeyPressed;
    NOP::SharedRule rlKeyReleased;

public:
    Game();
    ~Game();
    void movePlayer(int x, int y);
};