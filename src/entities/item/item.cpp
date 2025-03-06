#include "../../../include/entities/item/item.hpp"

namespace entities
{
    Item::Item(std::string kind, std::string texturePath) : kind(kind), owner(nullptr), attack(0)
    {
        texture = std::make_shared<Texture>();
        if (!texture->loadFromFile(texturePath))
        {
            throw std::runtime_error("Failed to load texture from " + texturePath);
        }
        sprite = std::make_shared<Sprite>(*texture);
    }

    Item::~Item()
    {
    }

    void Item::draw()
    {
        ptrGM->drawElement(*sprite);
    }

    sf::Drawable *Item::getDraw()
    {
        return sprite.get();
    }

    sf::Sprite *Item::getSprite()
    {
        return sprite.get();
    }

    bool Item::isProjectile()
    {
        return kind == "projectile";
    }

    bool Item::isMelee()
    {
        return kind == "melee";
    }

    bool Item::isShield()
    {
        return kind == "shield";
    }

    bool Item::isConsumable()
    {
        return kind == "consumable";
    }

    bool Item::isSolid()
    {
        return solid;
    }

    void Item::setupEventHandling(
        NOP::SharedAttribute<sf::Event::EventType> &atEventType,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY)
    {
    }

    const int Item::getAttack() const
    {
        return attack;
    }

    FloatRect Item::getGlobalBounds()
    {
        return sprite->getGlobalBounds();
    }

    void Item::scaleSprite(const float xFactor, const float yFactor)
    {
        sprite->scale(xFactor, yFactor);
        FloatRect bounds = sprite->getGlobalBounds();
        x = bounds.left;
        y = bounds.top;
    }

    void Item::setOriginToCenter()
    {
        FloatRect bounds = sprite->getLocalBounds();
        sprite->setOrigin(bounds.width / 2, bounds.height / 2);
        sprite->setPosition(x + bounds.width / 2, y + bounds.height / 2);
    }
}