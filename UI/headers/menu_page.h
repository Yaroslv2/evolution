#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include "page.h"
#include <string>

class MenuPage : protected Page
{
public:
    MenuPage(sf::RenderWindow *&, WindowState *&, sf::Font *&, float, float);
    ~MenuPage();
    void update();

private:
    enum class Buttons
    {
        START,
        SETTINGS,
        INFO,
        EXIT,
    };
    Buttons activeButton;
    void drawButton(std::string, float, float, sf::Color);
    sf::Text text;
    sf::RectangleShape rectangle;
    void processEvents();
    void draw();
    void moveUp();
    void moveDown();
};

#endif