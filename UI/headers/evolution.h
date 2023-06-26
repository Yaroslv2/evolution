#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "../../evolution/headers/World.h"
#include "window_state.h"
#include <SFML/Graphics.hpp>

class EvolutionPage
{
public:
    EvolutionPage(sf::RenderWindow *&, WindowState *&, sf::Font *&, float, float);
    ~EvolutionPage();
    void start(sf::Color);

private:
    void processingEvents();
    void draw(const std::vector<std::vector<Object *>> &); // draw on window
    void getNewScore(int, int);                            // push new score in deque
    int rectangleSize;                                     // size of rectangle on map
    int outlineTricknesSize;                               // size of trickness on map
    sf::RenderWindow *window;                              // window
    sf::RectangleShape rectangle;
    sf::RectangleShape optionsRectangle;
    sf::Text sfString; // string for text in window
    sf::Font font;
    sf::Color botsColor;
    bool pause;
    bool needDraw;
    int speed;
    int average;
    float width;
    float height;
    WindowState *state;
    std::deque<std::pair<int, int>> scores; // scores previous generations
    int era;
};

#endif