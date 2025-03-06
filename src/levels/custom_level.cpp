#include <fstream>
#include <filesystem>

#include "../../include/levels/level.hpp"
#include "../../include/game.hpp"
#include "../../include/levels/custom_level.hpp"
#include "../../include/entities/item/potion.hpp"

CustomLevel::CustomLevel(ColisionManager *colisionManager,
                         EventHandler *eventHandler,
                         Player *playerPtr,
                         Game *gamePtr,
                         Player *player2Ptr,
                         string path)
    : Level(colisionManager, eventHandler, playerPtr, gamePtr, player2Ptr)
{
    this->path = path;
    if (path != "")
    {
        buildLevel();
        return;
    }
    background = std::make_shared<BackgroundManager>("medieval_castle/background.png");
    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::White);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOutlineThickness(10);
    inputText.setPosition(Vector2f(100, 500));

    pathText.setFont(font);
    pathText.setCharacterSize(30);
    pathText.setFillColor(sf::Color::White);
    pathText.setOutlineColor(sf::Color::Black);
    pathText.setOutlineThickness(10);
    pathText.setPosition(Vector2f(50, 400));
    pathText.setString("Digite o caminho para o arquivo JSON de descricao de fase:");
}

CustomLevel::~CustomLevel()
{
    clearRules();
}

void CustomLevel::run()
{
    background->draw();
    if (path == "")
    {
        ptrGM->drawElement(pathText);
        ptrGM->drawElement(inputText);
        eventHandler->handleEvents();
    }
    else
    {
        handle_colisions();
        eventHandler->handleEvents();
        draw();
        changeState();
    }
}

void CustomLevel::changeState(int option)
{
    if (!player1Ptr->getAlive())
    {
        gamePtr->changeState(Game::States::RankingState, 0);
        return;
    }
    else if (colisionManager->getEnemyVector().empty())
    {
        gamePtr->changeState(Game::States::RankingState, 0);
        return;
    }

    Enemy *neutralizedEnemy = colisionManager->getNeutralizedEnemy();
    if (neutralizedEnemy)
    {
        Item *item = new Potion(neutralizedEnemy);
        colisionManager->addItem(item);
        entityList.append(item);
    }
}

void CustomLevel::createPlatformWithRandomThingsAbove(int xSize, int ySize, int posX, int posY)
{
}

void CustomLevel::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    if (path == "")
    {
        RULE(&rl2);
        LCONDITION();
        CEXP(atKeyPressed == sf::Keyboard::Return);
        END_CONDITION;
        ACTION();
        INSTIGATE(
            METHOD(
                atKeyPressed->SetValue(sf::Keyboard::Unknown);
                buildLevel();))
        END_ACTION;
        END_CONDITION;
        END_RULE;

        RULE(&rl1);
        LCONDITION();
        CEXP(atKeyPressed == sf::Keyboard::Key::Escape);
        END_CONDITION;
        ACTION();
        INSTIGATE(
            METHOD(
                changeState();))
        END_ACTION;
        END_CONDITION;
        END_RULE;

        RULE(&rl3);
        LCONDITION();
        CEXP(atEventType == sf::Event::TextEntered);
        END_CONDITION;
        ACTION();
        INSTIGATE(
            METHOD(
                char c = eventHandler->getEvent().text.unicode;
                if (c != 8 && c != 13)
                    playerInput += c;
                inputText.setString(playerInput);))
        END_ACTION;
        END_CONDITION;
        END_RULE;

        RULE(&rl4);
        LCONDITION();
        CEXP(atKeyPressed == sf::Keyboard::BackSpace);
        END_CONDITION;
        ACTION();
        INSTIGATE(
            METHOD(playerInput = playerInput.substring(0, playerInput.getSize() - 1);
                   inputText.setString(playerInput);))
        END_ACTION;
        END_CONDITION;
        END_RULE;
    }
}

json CustomLevel::readJson(string path)
{
    std::ifstream file(path);
    if (!file)
    {
        file.close();
        pathText.setString("Arquivo nao encontrado. Digite novamente seu caminho:");
        return json();
    }

    json j = json::parse(file);
    file.close();
    return j;
}

void CustomLevel::buildLevel()
{
    json j = readJson(playerInput.toAnsiString());
    if (j.empty())
        return;

    path = path == "" ? playerInput.toAnsiString() : path;
    string bg_path = j["background"];
    background = std::make_shared<BackgroundManager>(bg_path);

    auto entities = j["entities"];
    auto enemies = entities["enemies"];
    for (auto &enemy : enemies)
    {
        auto enemyType = enemy["type"];
        auto enemyX = enemy["x"];
        auto enemyY = enemy["y"];

        if (enemyType == "bat")
        {
            createBat(enemyX, enemyY);
            continue;
        }
        else if (enemyType == "bigNose")
        {
            createBigNose(enemyX, enemyY);
            continue;
        }
        else if (enemyType == "minotaur")
        {
            createMinotaur(enemyX, enemyY);
            continue;
        }
    }

    auto obstacles = entities["obstacles"];
    for (auto &obstacle : obstacles)
    {
        auto obstacleType = obstacle["type"];
        auto obstacleX = obstacle["x"];
        auto obstacleY = obstacle["y"];
        auto obstacleWidth = obstacle["width"];
        auto obstacleHeight = obstacle["height"];

        if (obstacleType == "bush")
        {
            createBush(obstacleX, obstacleY);
            continue;
        }
        else if (obstacleType == "fire")
        {
            createFire(obstacleX, obstacleY);
            continue;
        }
        else if (obstacleType == "platform")
        {
            createPlatform(obstacleWidth, obstacleHeight, obstacleX, obstacleY);
            continue;
        }
        else if (obstacleType == "wall")
        {
            createWall(obstacleHeight, obstacleX, obstacleY);
            continue;
        }
    }

    auto playerPos = entities["playerPos"];
    player1Ptr->setX(playerPos["x"]);
    player1Ptr->setY(playerPos["y"]);
    player1Ptr->getSprite()->setPosition(playerPos["x"], playerPos["y"]);

    if (player2Ptr)
    {
        player2Ptr->setX(playerPos["x"]);
        player2Ptr->setY(playerPos["y"]);
        player2Ptr->getSprite()->setPosition(playerPos["x"], playerPos["y"]);
    }
}

void CustomLevel::clearRules()
{
    rl1->SetCondition(c1);
    rl2->SetCondition(c1);
    rl3->SetCondition(c1);
    rl4->SetCondition(c1);
}