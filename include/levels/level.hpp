#pragma once
#include "../utils/state.hpp"
#include "../utils/ente.hpp"
#include "../managers/colision_manager.hpp"
#include "../managers/graphic_manager.hpp"
#include "../managers/event_handler.hpp"
#include "../lists/entities.hpp"
#include "../ui/background_manager.hpp"
#include "../entities/characters/players/player1.hpp"
#include "../entities/characters/enemies/minotaur.hpp"
#include <memory>
// #include "../Entidades/Personagens/jogador2.hpp"

using namespace managers;
using lists::EntityList;

namespace levels
{
    class Level : public Ente, public State
    {
    protected:
        ColisionManager *colisionManager;
        EventHandler *eventHandler;
        EntityList entityList;
        Player *player1Ptr, *player2Ptr;
        std::shared_ptr<BackgroundManager> background;
        int bigNoseCount = 0, batCount = 0;

    public:
        Level(ColisionManager *colisionManager = nullptr,
              EventHandler *eventHandler = nullptr,
              Player *playerPtr = nullptr,
              Game *gamePtr = nullptr,
              Player *player2Ptr = nullptr);
        virtual ~Level();
        virtual void run();
        void setupEventHandling(
            NOP::SharedAttribute<sf::Event::EventType> &atEventType,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
            NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
            NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
            NOP::SharedAttribute<int> &atMousePositionX,
            NOP::SharedAttribute<int> &atMousePositionY);
        void draw();
        void handle_colisions();
        virtual void changeState(int option = 0) = 0;
        void createPlatform(int xSize, int ySize, int posX, int posY);
        void createWall(int ySize, int posX, int posY);
        void createBigNose(int posX, int posY);
        void createBush(int posX, int posY);
        void createFire(int posX, int posY);
        void createBat(int posX, int posY);
        void createMinotaur(int posX, int posY);
        void createProjectile(entities::characters::Minotaur *minotaurPtr);
        virtual void createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY) = 0;
    };
}
