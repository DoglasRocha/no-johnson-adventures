#include "../include/ui/ranking.hpp"
#include <fstream>
#include <sstream>

Ranking::Ranking(EventHandler *eventHandler, Game *gamePtr)
    : eventHandler(eventHandler), gamePtr(gamePtr)
{
    background = std::make_shared<BackgroundManager>("menu/background.png");
    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");

    try
    {
        ifstream file;
        file.open("../ranking.txt");
        if (file)
            readFile();
        else
            throw(ifstream::failure("Erro na abertura do arquivo"));
    }
    catch (ifstream::failure f)
    {
        ofstream file("../ranking.txt");
        file.write("", 0);
    }

    font.loadFromFile("../assets/VCR_OSD_MONO.ttf");

    inputText.setFont(font);
    inputText.setCharacterSize(75);
    inputText.setFillColor(sf::Color::White);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOutlineThickness(10);
    inputText.setPosition(Vector2f(100, 500));

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(75);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(10);
    gameOverText.setPosition(Vector2f(50, 400));
    gameOverText.setString("GAME OVER. Digite seu nome:");
}

Ranking::~Ranking()
{
    rl1->SetCondition(c1);
    rl2->SetCondition(c1);
    rl3->SetCondition(c1);
}

void Ranking::run()
{
    draw();
    eventHandler->handleEvents();
}

void Ranking::setupEventHandling(
    NOP::SharedAttribute<sf::Event::EventType> &atEventType,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
    RULE(&rl1);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Escape);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(changeState();))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl2);
    LCONDITION();
    CEXP(atKeyPressed == sf::Keyboard::Return);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(writeFile(gamePtr->getScore());))
    END_ACTION;
    END_CONDITION;
    END_RULE;

    RULE(&rl3);
    LCONDITION();
    CEXP(atEventType == sf::Event::TextEntered);
    END_CONDITION;
    ACTION();
    INSTIGATE(
        METHOD(playerInput += eventHandler->getEvent().text.unicode;
               inputText.setString(playerInput);))
    END_ACTION;
    END_CONDITION;
    END_RULE;
}

void Ranking::draw()
{
    background->draw();
    if (gamePtr->getScore())
    {
        ptrGM->drawElement(inputText);
        ptrGM->drawElement(gameOverText);
    }
    else
        drawPlayers();
}

void Ranking::changeState(int option)
{
    gamePtr->changeState(Game::States::MenuState, 0);
}

void Ranking::readFile()
{
    ifstream file("../ranking.txt");

    PlayerInfo aux;

    while (!file.eof())
    {
        file >> aux.name >> aux.score;
        if (aux.score)
            rankingList.push_back(aux);
    }

    file.close();
}

void Ranking::writeFile(int points)
{
    std::ofstream file("../ranking.txt", std::ofstream::trunc);
    if (!file)
    {
        std::cerr << "Erro na abertura do arquivo" << std::endl;
        return;
    }

    PlayerInfo aux;

    string auxInput = playerInput.toAnsiString();
    aux.name = auxInput.substr(0, 3);
    aux.score = points;

    rankingList.push_back(aux);

    std::sort(rankingList.begin(), rankingList.end(), [](const PlayerInfo &a, const PlayerInfo &b)
              { return a.score > b.score; });

    if (rankingList.size() > 10)
        rankingList.resize(10);

    for (auto &player : rankingList)
    {
        file << player.name << ' ' << player.score << std::endl;
    }

    file.close();
    gamePtr->resetScore();
}

void Ranking::drawPlayers()
{
    for (int i = 0; i < rankingList.size(); i++)
    {
        Text aux, aux2, divider;
        aux.setString(rankingList[i].name);
        aux2.setString(to_string(rankingList[i].score));
        divider.setString(" - ");

        aux.setFont(font);
        aux.setCharacterSize(75);
        aux.setFillColor(sf::Color::White);
        aux.setOutlineColor(sf::Color::Black);
        aux.setOutlineThickness(10);
        aux.setPosition(Vector2f(200, 75 * (i + 1)));

        aux2.setFont(font);
        aux2.setCharacterSize(75);
        aux2.setFillColor(sf::Color::White);
        aux2.setOutlineColor(sf::Color::Black);
        aux2.setOutlineThickness(10);
        aux2.setPosition(Vector2f(1000, 75 * (i + 1)));

        divider.setFont(font);
        divider.setCharacterSize(75);
        divider.setFillColor(sf::Color::White);
        divider.setOutlineColor(sf::Color::Black);
        divider.setOutlineThickness(10);
        divider.setPosition(Vector2f(690, 75 * (i + 1)));

        ptrGM->drawElement(aux);
        ptrGM->drawElement(aux2);
        ptrGM->drawElement(divider);
    }
}