#pragma once
#include "graphic_manager.hpp"
#include <SFML/Graphics.hpp>

namespace managers
{
    class EventHandler
    {
    protected:
        GraphicManager *ptrGM;
        static EventHandler *instance;
        EventHandler();

    public:
        ~EventHandler();
        static EventHandler *getInstance();
        static void deleteInstance();
        void setGraphicManager(GraphicManager *ptrGM);
        bool getEvent(sf::Event &event);
    };
}