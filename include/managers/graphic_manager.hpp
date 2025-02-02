#pragma once
#include <SFML/Graphics.hpp>
// #include <libnop/fbe.h>
#include <memory>

namespace managers
{
    class GraphicManager
    {
    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::unique_ptr<sf::View> view;
        static GraphicManager *instance;

    protected:
        GraphicManager();

    public:
        ~GraphicManager();
        static GraphicManager *getInstance();
        static void deleteInstance();
        std::shared_ptr<sf::RenderWindow> getWindow();
        const bool checkWindowOpen();
        void clearWindow();
        void drawElement(sf::Drawable &drawable);
        void showElements();
        void closeWindow();
        sf::Vector2u getWindowSize();
        void centerWindow(int x);
        sf::Vector2f getCenterView();
    };
}
