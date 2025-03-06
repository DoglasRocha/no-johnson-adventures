#pragma once
#include "../entity.hpp"
#include "../../lists/texture.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace lists;

namespace entities::characters
{
    class Character : public Entity
    {
    protected:
        int lives, jumps, attack;
        bool alive;
        Sprite sprite;
        TextureList textures;
        TextureList::Node *currentNode;
        std::string direction;
        Clock animationClock;
        const sf::Time animationTick;

    public:
        Character();
        virtual ~Character();
        virtual void moveX();
        virtual void moveY();
        void setJumps(const int jumps);
        int getJumps() const;
        Drawable *getDraw();
        Sprite *getSprite();
        virtual void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY) = 0;
        std::string getDirection() const;
        void setDirection(const std::string direction);
        void setOriginToCenter();
        void setThrust(const int thrust);
        void loadTextures(const std::string path, const int start, const int end);
        void scaleSprite(const float xFactor, const float yFactor);
        void animate();
        void resetAnimation();
        void draw();
        virtual void collideX() = 0;
        virtual void collideY();
        virtual int getAttack();
        virtual void sufferAttack(Character *character);
        void sufferAttack(int damage);
        void checkAlive();
        bool getAlive() const;
        virtual void slowness() = 0;
        virtual void burn() = 0;
        FloatRect getGlobalBounds();
        virtual int getBaseLives() = 0;
    };
}
