#pragma once
class Game;

class State
{
protected:
    Game *gamePtr;

public:
    State(Game *gamePtr = nullptr);
    virtual ~State();
    virtual void changeState(int option = 0) = 0;
    virtual void run() = 0;
};