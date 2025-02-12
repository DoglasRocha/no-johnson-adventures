#pragma once

#include "../utils/ente.hpp"
#include "../managers/graphic_manager.hpp"
#include <string>
#include <SFML/Graphics.hpp>

using managers::GraphicManager;

class BackgroundManager : public Ente
{
private:
    std::string path;
    sf::RectangleShape backgroundImage;
    std::shared_ptr<sf::Texture> texture;

public:
    BackgroundManager(const std::string pathToImage = "");
    ~BackgroundManager();
    void draw();
    void setupEventHandling(
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyPressed,
        NOP::SharedAttribute<sf::Keyboard::Key> &atKeyReleased,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonPressed,
        NOP::SharedAttribute<sf::Mouse::Button> &atMouseButtonReleased,
        NOP::SharedAttribute<int> &atMousePositionX,
        NOP::SharedAttribute<int> &atMousePositionY);
};