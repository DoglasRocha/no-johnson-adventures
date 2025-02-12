//
// Created by doglasrocha on 11/4/22.
//

#ifndef JOGO_TECNICAS_PROGRAMACAO_LISTA_ENTIDADES_HPP
#define JOGO_TECNICAS_PROGRAMACAO_LISTA_ENTIDADES_HPP
#include "../entities/characters/players/player.hpp"
#include "circular.hpp"
#include "../entities/entity.hpp"

using entities::characters::Player;

namespace lists
{
    class EntityList : public CircularList<entities::Entity>
    {
    public:
        EntityList() : CircularList<entities::Entity>()
        {
        }

        ~EntityList()
        {
        }

        void drawEntities()
        {
            Node *node;
            for (node = head; node != tail; node = node->getNext())
            {
                node->getData()->draw();
            }
            node->getData()->draw();
        }

        void clearList()
        {
            Node *aux;
            for (aux = head; aux != tail; aux = aux->getNext())
            {
                if (!dynamic_cast<Player *>(aux->getData()))
                {
                    delete aux->getData();
                }
            }
            if (!dynamic_cast<Player *>(aux->getData()))
                delete aux->getData();
        }
    };
}

#endif // JOGO_TECNICAS_PROGRAMACAO_LISTA_ENTIDADES_HPP
