#pragma once
#include "../entity.hpp"
#include "../characters/character.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

using namespace sf;

namespace entities
{
    class Item : public Entity
    {
    protected:
        std::string kind;
        bool solid;
        int attack;
        std::shared_ptr<Texture> texture;
        std::shared_ptr<Sprite> sprite;
        std::string direction;
        characters::Character *owner;

    public:
        Item(std::string kind, std::string texturePath);
        ~Item();
        void draw();
        virtual void setThrust(int thrust) = 0;
        sf::Drawable *getDraw();
        sf::Sprite *getSprite();
        virtual bool isProjectile();
        virtual bool isMelee();
        virtual bool isShield();
        virtual bool isConsumable();
        virtual bool isSolid();
        virtual void collideX() = 0;
        virtual void collideY() = 0;
        virtual void interact(characters::Character *character) = 0;
        void setupEventHandling(
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        const int getAttack() const;
        virtual void moveX() = 0;
        virtual void moveY() = 0;
    };
}