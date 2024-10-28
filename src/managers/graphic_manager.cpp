#include <SFML/Graphics.hpp>
#include "../../include/managers/graphic_manager.hpp"

using managers::GraphicManager;

GraphicManager::
    GraphicManager() : window(new sf::RenderWindow(sf::VideoMode(1400, 1000), "No Johnson Adventures")),
                       view(new sf::View({700, 500}, {1400, 1000}))
{
    window->setFramerateLimit(40);
    window->setView(*view);
}

GraphicManager::
    ~GraphicManager()
{
}

GraphicManager *GraphicManager::getInstance()
{
    if (instance == nullptr)
        instance = new GraphicManager();

    return instance;
}

void GraphicManager::deleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

std::shared_ptr<sf::RenderWindow> GraphicManager::getWindow()
{
    return window;
}

const bool GraphicManager::checkWindowOpen()
{
    return window->isOpen();
}

void GraphicManager::clearWindow()
{
    window->clear();
}

void GraphicManager::drawElement(sf::Drawable &drawable)
{
    window->draw(drawable);
}

void GraphicManager::showElements()
{
    window->display();
}

void GraphicManager::closeWindow()
{
    window->close();
}

sf::Vector2u GraphicManager::getWindowSize()
{
    return window->getSize();
}

void GraphicManager::centerWindow(int x)
{
    view->setCenter(x, 500);
    window->setView(*view);
}

sf::Vector2f GraphicManager::getCenterView()
{
    return view->getCenter();
}
