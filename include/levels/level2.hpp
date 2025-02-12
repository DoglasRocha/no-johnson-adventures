#pragma once
#include "level.hpp"

using levels::Level;

class Level2 : public Level
{
private:
    int fireCount = 0;

public:
    Level2(ColisionManager *colisionManager = nullptr,
           EventHandler *eventHandler = nullptr,
           Player *playerPtr = nullptr,
           Game *gamePtr = nullptr); //,
    //   Jogador *ptrJogador2_ = nullptr);
    ~Level2();
    void changeState(int option = 0);
    void createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY);
};