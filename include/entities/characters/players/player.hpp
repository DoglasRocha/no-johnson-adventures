#pragma once
#include "../character.hpp"
#include <SFML/Graphics.hpp>

using entities::characters::Character;
using namespace sf;

namespace entities::characters
{
    class Player : public Character
    {
    private:
        int score = 0;

        // protected:
        //     Text textoBarraVida;
        //     Font font;

    public:
        Player();
        virtual ~Player();
        virtual void setupEventHandling(
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY) = 0;
        void collideX();
        virtual void moveX();
        void pushX(const int direction);
        void pushY();
        void slowness();
        void burn();
        void reset();
        // virtual void desenhaBarraVida() = 0;
        void resetScore();
        int getScore();
        void addScore(int score);
    };
}
