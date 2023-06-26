#ifndef INFO_PAGE_H
#define INFO_PAGE_H

#include "page.h"
#include <fstream>
#include <vector>

class InfoPage : protected Page
{
public:
    InfoPage(sf::RenderWindow *&, WindowState *&, sf::Font *&font, float, float);
    ~InfoPage();
    void update();

private:
    void draw();
    void processEvents();
    sf::Text text;
    sf::RectangleShape rectangle;
    std::ifstream infoFile;
    std::vector<std::vector<sf::Color>> map;
};

#endif