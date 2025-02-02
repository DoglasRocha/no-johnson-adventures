//
// Created by doglasrocha on 11/1/22.
//

#ifndef JOGO_TECNICAS_PROGRAMACAO_PLATAFORMA_HPP
#define JOGO_TECNICAS_PROGRAMACAO_PLATAFORMA_HPP
#include "obstacle.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace entities::obstacles
{
    class Platform : public Obstacle
    {

    public:
        Platform(const int sizeX, const int sizeY, const int x, const int y);
        ~Platform();
        void interact(Character *playerPtr);
    };
}

#endif // JOGO_TECNICAS_PROGRAMACAO_PLATAFORMA_HPP
