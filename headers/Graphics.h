#ifndef Graphics_h
#define Graphics_h

#include <SFML/Graphics.hpp>
#include "World.h"

class Graphics {
    int rectangleSize;
    int outlineTricknesSize;
    sf::RenderWindow window; //(sf::VideoMode(1500, 700), "Evolution, baby");
    sf::RectangleShape rectangle;
public:
    enum class Event { CLOSE };
    Graphics();
    void Draw(const std::vector<std::vector<Object*>>&);
    void CloseWindow();
    bool IsWindowOpen();
    std::vector<Graphics::Event> GetWindowEvents();
};

#endif
