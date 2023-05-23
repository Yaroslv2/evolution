#ifndef Graphics_h
#define Graphics_h

#include <SFML/Graphics.hpp>
#include "World.h"
#include <deque>

class Graphics
{
    int rectangleSize;       // size of rectangle on map
    int outlineTricknesSize; // size of trickness on map
    sf::RenderWindow window; // window
    sf::RectangleShape rectangle;
    sf::Text sfString; // string for text in window
    sf::Font font;
    std::deque<std::pair<int, int>> scores; // scores previous generations
    sf::View view;

public:
    enum class Event // windows events
    {
        CLOSE,
        PAUSE,
        INCREASE_SPEED,
        DECREASE_SPEED,
        SWITCH_DRAW,
    };
    Graphics();
    void Draw(const std::vector<std::vector<Object *>> &, int); // draw on window
    void CloseWindow();
    bool IsWindowOpen();
    std::vector<Graphics::Event> GetWindowEvents(); // processing and return windows events
    void getNewScore(int, int);                     // push new score in deque
};

#endif
