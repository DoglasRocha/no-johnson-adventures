#pragma once
#include "custom_level.hpp"

class TestLevel : public CustomLevel
{
private:
    NOP::SharedAttribute<sf::Time> atElapsedTime{NOP::BuildAttribute(sf::Time::Zero)};
    sf::Clock clock;

public:
    TestLevel(ColisionManager *colisionManager = nullptr,
              EventHandler *eventHandler = nullptr,
              Player *playerPtr = nullptr,
              Game *gamePtr = nullptr);
    ~TestLevel();
    void run();
    void update();
};