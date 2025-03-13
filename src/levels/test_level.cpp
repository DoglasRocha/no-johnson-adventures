#include "../../include/levels/test_level.hpp"
#include "../../include/lists/circular.hpp"

TestLevel::TestLevel(ColisionManager *colisionManager, EventHandler *eventHandler, Player *playerPtr, Game *gamePtr)
    : CustomLevel(colisionManager, eventHandler, playerPtr, gamePtr, nullptr, "../custom_level.json")
{
    background = std::make_shared<BackgroundManager>("pixel_art_forest/background.png");

    atPlayerAlive->SetValue(player1Ptr->getAlive());
    atEnemyNeutralizedPtr->SetValue(colisionManager->getNeutralizedEnemy());
    atEnemyCount->SetValue(colisionManager->getEnemyVector().size());

    RULE();
    LCONDITION();
    CEXP(atElapsedTime >= sf::seconds(1));
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(
            int enemyToKill = rand() % this->atEnemyCount->GetValue();
            CircularList<Entity>::Node *node = entityList.begin();
            for (int i = 0; i < enemyToKill; i++) {
                node = node->getNext();
            }

            Entity *entity = node->getData();
            Enemy *enemy = dynamic_cast<Enemy *>(entity);
            while (!enemy || !enemy->getAlive()) {
                node = node->getNext();
                entity = node->getData();
                enemy = dynamic_cast<Enemy *>(entity);
            }

            enemy->sufferAttack(1000);

            atElapsedTime->SetValue(sf::Time::Zero);
            clock.restart();))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}

TestLevel::~TestLevel()
{
}

void TestLevel::run()
{
    handle_colisions();
    eventHandler->handleEvents();
    draw();
    update();
}

void TestLevel::update()
{
    atElapsedTime->SetValue(clock.getElapsedTime());
}