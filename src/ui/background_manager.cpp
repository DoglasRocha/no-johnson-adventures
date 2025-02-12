#include "../../include/ui/background_manager.hpp"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

BackgroundManager::BackgroundManager(const std::string pathToImage) : path(pathToImage), texture(std::make_shared<sf::Texture>())
{
    std::stringstream buffer;
    buffer << "../assets/" << path;
    if (!texture->loadFromFile(buffer.str()))
    {
        throw std::runtime_error("Failed to load background image from path: " + path);
    }

    sf::Vector2u windowSize = ptrGM->getWindowSize(),
                 imageSize = texture->getSize();

    float xScale = (float)windowSize.x / imageSize.x,
          yScale = (float)windowSize.y / imageSize.y;

    backgroundImage.setTexture(texture.get());
    backgroundImage.setSize(sf::Vector2f(windowSize.x, windowSize.y));
}

BackgroundManager::~BackgroundManager()
{
}

void BackgroundManager::draw()
{
    sf::Vector2f viewPosition = ptrGM->getCenterView();
    backgroundImage.setPosition(viewPosition.x - 700, viewPosition.y - 500);
    ptrGM->drawElement(backgroundImage);
}

void BackgroundManager::setupEventHandling(
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
    NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
    NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
    NOP::SharedAttribute<int> &atMousePositionX,
    NOP::SharedAttribute<int> &atMousePositionY)
{
}