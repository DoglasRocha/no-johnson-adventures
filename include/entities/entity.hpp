#pragma once
#include "../utils/ente.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/graphic_manager.hpp"

using managers::GraphicManager;

namespace entities
{
    class Entity : public Ente
    {
    protected:
        int thrust = 0, x, y, velX, velY;

    public:
        Entity();
        virtual ~Entity();
        virtual void run();
        virtual void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY) = 0;
        virtual void draw() = 0;
        int getThrust() const;
        virtual void setThrust(int thrust) = 0;
        virtual sf::Drawable *getDraw() = 0;
        virtual int getX() const;
        virtual int getY() const;
        virtual void setX(const int x);
        virtual void setY(const int y);
        virtual void setVelX(const int vel);
        virtual void setVelY(const int vel);
        virtual int getVelX() const;
        virtual int getVelY() const;
        virtual sf::FloatRect getGlobalBounds() = 0;
    };
}