#pragma once
#include "../entity.hpp"
#include "../characters/players/player.hpp"
#include <memory>

using entities::Entity;
using entities::characters::Character;
using namespace sf;

namespace entities::obstacles
{
    class Obstacle : public Entity
    {
    protected:
        int xSize, ySize;
        std::shared_ptr<Shape> shape;
        std::shared_ptr<Texture> texture;
        bool isSolid = 1;

    public:
        Obstacle();
        Obstacle(const int sizeX, const int sizeY);
        Obstacle(const int sizeX, const int sizeY, const int x, const int y);
        virtual ~Obstacle();
        int getSizeX() const;
        void setSizeX(const int sizeX);
        int getSizeY() const;
        void setSizeY(const int sizeY);
        Drawable *getDraw();
        Shape *getShape();
        void draw();
        bool getIsSolid() const;
        virtual void interact(Character *playerPtr) = 0;
        void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        void setThrust(int thrust);
    };
}
