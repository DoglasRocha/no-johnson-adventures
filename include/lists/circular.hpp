//
// Created by doglasrocha on 10/28/22.
//

#ifndef JOGO_TECNICAS_PROGRAMACAO_LISTA_CIRCULAR_HPP
#define JOGO_TECNICAS_PROGRAMACAO_LISTA_CIRCULAR_HPP
#include <iostream>

namespace Lists
{

    template <class T>
    class CircularList
    {

    public:
        class Node
        {
        private:
            Node *next;
            T *data;

        public:
            Node(T *data = nullptr)
            {
                this->data = data;
            }

            ~Node() {}

            void setNext(Node *next)
            {
                this->next = next;
            }

            Node *getNext()
            {
                return next;
            }

            void setData(T *data)
            {
                this->data = data;
            }

            T *getData()
            {
                return data;
            }

            Node *operator++()
            {
                return next;
            }
        };

    protected:
        Node *head, *tail;
        int length;

    public:
        CircularList()
        {
            head = tail = nullptr;
            length = 0;
        }

        virtual ~CircularList()
        {
            Node *tmp;
            for (Node *aux = head; aux != tail; aux = tmp)
            {
                tmp = aux->getNext();
                delete aux;
            }
            delete tmp;
        }

        Node *begin() const
        {
            return head;
        }

        Node *end() const
        {
            return tail;
        }

        ListaCircular<T> *append(T *data)
        {
            Node *node = new Node(data);
            if (length == 0)
            {
                head = tail = node;
                head->setNext(node);
                tail->setNext(node);
                length++;
                return this;
            }

            node->setNext(tail->getNext());
            tail->setNext(node);
            tail = node;
            length++;
            return this;
        }

        int getLength() const
        {
            return length;
        }

        virtual void clearList() = 0;
    };
}

#endif // JOGO_TECNICAS_PROGRAMACAO_LISTA_CIRCULAR_HPP
