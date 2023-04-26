#include "../headers/Graphics.h"

Graphics::Graphics() : rectangleSize(20), outlineTricknesSize(2)
{
    window.create(sf::VideoMode(1500, 700), "Evolution");
    window.setFramerateLimit(60);
    rectangle.setSize(sf::Vector2f(rectangleSize, rectangleSize));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(2);
}

void Graphics::Draw(const std::vector<std::vector<Object *>> &pole)
{
    window.clear();
    for (int i = 0; i < pole.size(); i++)
    {
        for (int j = 0; j < pole[i].size(); j++)
        {
            switch (pole[i][j]->GetType())
            {
            case Object::Type::BOT:
                rectangle.setFillColor(sf::Color::Blue);
                break;
            case Object::Type::POISON:
                rectangle.setFillColor(sf::Color::Red);
                break;
            case Object::Type::EAT:
                rectangle.setFillColor(sf::Color::Green);
                break;
            case Object::Type::WALL:
                rectangle.setFillColor(sf::Color(160, 160, 160));
                break;
            case Object::Type::EMPTY:
                rectangle.setFillColor(sf::Color::Black);
                break;
            default:
                break;
            }
            rectangle.setPosition(i * rectangleSize + outlineTricknesSize, j * rectangleSize + outlineTricknesSize);
            window.draw(rectangle);
        }
    }
    window.display();
}

void Graphics::CloseWindow()
{
    window.close();
}

bool Graphics::IsWindowOpen()
{
    return window.isOpen();
}

std::vector<Graphics::Event> Graphics::GetWindowEvents()
{
    std::vector<Event> result;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            CloseWindow();
            result.emplace_back(Event::CLOSE);
        }
    }

    return result;
}