#pragma once
#include "../utils/state.hpp"
#include "../utils/ente.hpp"
#include "../managers/colision_manager.hpp"
#include "../managers/graphic_manager.hpp"
#include "../managers/event_handler.hpp"
#include "../lists/entities.hpp"
// #include "../background_manager.hpp"
#include "../entities/characters/player1.hpp"
// #include "../Entidades/Personagens/jogador2.hpp"

using namespace managers;
using lists::entityList;

namespace levels
{
    class Level : public Ente, public State
    {
    protected:
        ColisionManager *colisionManager;
        EventHandler *EventHandler;
        EntityList entityList;
        Player *player1Ptr; //, *player2Ptr;
        // BackgroundManager *planoDeFundo;
        int bigNoseCount = 0, batCount = 0;

    public:
        Level(GerenciadorColisoes *gC = nullptr,
              GerenciadorEventos *gE = nullptr,
              Jogador *ptrJogador_ = nullptr,
              Jogo *ptrJogo = nullptr,
              Jogador *ptrJogador2_ = nullptr);
        virtual ~Level();
        virtual void executar();
        virtual void processaEventos();
        void desenhar();
        void gerencia_colisoes();
        virtual void trocaEstado(int opcao = 0) = 0;
        void criaPlataforma(int tamX, int tamY, int posX, int posY);
        void criaParede(int tamY, int posX, int posY);
        void criaNarigudo(int posX, int posY);
        void criaArbusto(int posX, int posY);
        void criaFogo(int posX, int posY);
        void criaMorcego(int posX, int posY);
        virtual void criaPlataformaComAgregadosAleatorios(int tamX, int tamY, int posX, int posY) = 0;
    };
}
