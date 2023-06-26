#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "page.h"
#include <vector>

class SettingsPage : protected Page
{
public:
    SettingsPage(sf::RenderWindow *&, WindowState *&, sf::Font *&, float, float, sf::Color *&);
    ~SettingsPage();
    void update();

private:
    void draw();
    void processEvents();
    void moveLeft();
    void moveRight();
    sf::Text text;
    std::vector<sf::Color> colors;
    int activeColorIdx;
    sf::Color *savedColor;
    sf::RectangleShape rectangle;
};

#endif