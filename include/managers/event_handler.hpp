#pragma once
#include "graphic_manager.hpp"
#include <SFML/Graphics.hpp>
#include <libnop/framework.h>
#include "../utils/ente.hpp"
#include <memory>

namespace managers
{
    class EventHandler : NOP::FBE
    {
    private:
        Ente *player;
        sf::Event event;
        NOP::SharedAttribute<sf::Event::EventType> atEventType{
            NOP::BuildAttribute(sf::Event::EventType::GainedFocus)};
        NOP::SharedAttribute<sf::Keyboard::Key> atKeyPressed{
            NOP::BuildAttribute(sf::Keyboard::Unknown)};
        NOP::SharedAttribute<sf::Keyboard::Key> atKeyReleased{
            NOP::BuildAttribute(sf::Keyboard::Unknown)};
        NOP::SharedAttribute<sf::Mouse::Button> atMouseButtonPressed{
            NOP::BuildAttribute(sf::Mouse::Middle)};
        NOP::SharedAttribute<sf::Mouse::Button> atMouseButtonReleased{
            NOP::BuildAttribute(sf::Mouse::Middle)};
        NOP::SharedAttribute<int> atMousePositionX{NOP::BuildAttribute(-1)};
        NOP::SharedAttribute<int> atMousePositionY{NOP::BuildAttribute(-1)};

    protected:
        std::weak_ptr<GraphicManager> ptrGM;
        static EventHandler *instance;
        EventHandler();

    public:
        ~EventHandler();
        static EventHandler *getInstance();
        static void deleteInstance();
        void setGraphicManager(std::shared_ptr<GraphicManager> ptrGM);
        bool pollEvent();
        sf::Event getEvent();
        void setPlayer(Ente *player);
        void subscribe(Ente *ente);
        void handleEvents();
    };
}