#include "../../include/utils/state.hpp"
#include "../../include/game.hpp"

State::State(Game *gamePtr)
{
    this->gamePtr = gamePtr;
}

State::~State() {}