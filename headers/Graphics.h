#ifndef Graphics_h
#define Graphics_h

#include <SFML/Graphics.hpp>
#include "World.h"
#include <deque>

class Graphics
{
    int rectangleSize;
    int outlineTricknesSize;
    sf::RenderWindow window; //(sf::VideoMode(1500, 700), "Evolution, baby");
    sf::RectangleShape rectangle;
    sf::Text sfString;
    sf::Font font;
    std::deque<std::pair<int, int>> scores;

public:
    enum class Event
    {
        CLOSE,
        PAUSE,
    };
    Graphics();
    void Draw(const std::vector<std::vector<Object *>> &, int);
    void CloseWindow();
    bool IsWindowOpen();
    std::vector<Graphics::Event> GetWindowEvents();
    void getNewScore(int, int);
};

#endif
