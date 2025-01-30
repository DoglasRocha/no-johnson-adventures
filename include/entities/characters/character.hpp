#pragma once
#include "../entity.hpp"
// #include "../../listas/lista_texturas.hpp"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
// using namespace Listas;

namespace entities::characters
{
    class Character : public Entity
    {
    protected:
        int lives, jumps, attack;
        bool alive;
        // Sprite sprite;
        RectangleShape sprite;
        // ListaTexturas listaTexturas;
        // ListaTexturas::Node *noAtual;
        std::string direction;
        // Clock relogioAnimacao;
        // const sf::Time tempoAnimacao;

    public:
        Character();
        virtual ~Character();
        virtual void moveX();
        virtual void moveY();
        void setJumps(const int jumps);
        int getJumps() const;
        Drawable *getDraw();
        // Sprite *getSprite();
        RectangleShape *getSprite();
        virtual void setupEventHandling(
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
        // void carregarTexturas(const std::string endereco, const int comeco, const int fim);
        // void escalarSprite(const float fatorX, const float fatorY);
        // void animar();
        // void resetAnimacao();
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
    };
}
