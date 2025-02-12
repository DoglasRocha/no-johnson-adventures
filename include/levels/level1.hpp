#pragma once
#include "level.hpp"

using levels::Level;

class Level1 : public Level
{
private:
    int bushCount = 0;

public:
    Level1(ColisionManager *colisionManager = nullptr,
           EventHandler *eventHandler = nullptr,
           Player *playerPtr = nullptr,
           Game *gamePtr = nullptr); //,
    //   Jogador *ptrJogador2_ = nullptr);
    ~Level1();
    void changeState(int option = 0);
    void createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY);
};