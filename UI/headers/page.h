#ifndef PAGE_H
#define PAGE_H

#include "window_state.h"
#include <SFML/Graphics.hpp>

class Page
{
public:
    Page(sf::RenderWindow *&, WindowState *&, sf::Font *&font, float, float);
    virtual void update() = 0;
    virtual ~Page();

protected:
    virtual void draw() = 0;
    virtual void processEvents() = 0;
    sf::RenderWindow *window;
    WindowState *state;
    sf::Font *font;
    float width;
    float height;
};

#endif