#include "../include/ente.hpp"

Ente::Ente()
{
}

Ente::~Ente()
{
}

void Ente::run()
{
}

void Ente::setGraphicManager(std::shared_ptr<GraphicManager> ptrGM_)
{
    ptrGM = &*ptrGM_;
}