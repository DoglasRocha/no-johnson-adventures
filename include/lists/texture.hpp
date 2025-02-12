//
// Created by doglasrocha on 11/4/22.
//

#ifndef JOGO_TECNICAS_PROGRAMACAO_LISTA_TEXTURAS_HPP
#define JOGO_TECNICAS_PROGRAMACAO_LISTA_TEXTURAS_HPP
#include "circular.hpp"
#include <SFML/Graphics.hpp>

namespace lists
{
    class TextureList : public CircularList<sf::Texture>
    {
    public:
        TextureList() : CircularList<sf::Texture>()
        {
        }

        ~TextureList()
        {
        }

        void clearList()
        {
            Node *aux;
            for (aux = head; aux != tail; aux = aux->getNext())
            {
                delete aux->getData();
            }
            delete aux->getData();
        }
    };
}

#endif // JOGO_TECNICAS_PROGRAMACAO_LISTA_TEXTURAS_HPP
