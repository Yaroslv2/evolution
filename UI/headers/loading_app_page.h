#ifndef LOADING_APP_PAGE_H
#define LOADING_APP_PAGE_H

#include "page.h"

class LoadingAppPage : protected Page
{
public:
    LoadingAppPage(sf::RenderWindow *&, WindowState *&, sf::Font *&, float, float);
    ~LoadingAppPage();
    void update();

private:
    sf::Text text;
    void processEvents();
    void draw();
};

#endif