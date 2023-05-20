#include "../headers/Graphics.h"
#include <iostream>
#include <string>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1500
#define MAP_X_COORD 325
#define MAP_Y_COORD 125

#define FONT_FILE "/home/onefore/projects/course-paper/assets/Roboto/Roboto-Bold.ttf"

Graphics::Graphics() : rectangleSize(20), outlineTricknesSize(2)
{
    window.create(sf::VideoMode(1500, 700), "Evolution");
    window.setFramerateLimit(60);
    rectangle.setSize(sf::Vector2f(rectangleSize, rectangleSize));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(outlineTricknesSize);
    if (!font.loadFromFile(FONT_FILE))
    {
        std::cout << "Error: cannot load font from file" << std::endl;
    }
    sfString.setFont(font);
    sfString.setFillColor(sf::Color::White);
}

void Graphics::Draw(const std::vector<std::vector<Object *>> &pole, int era)
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
            rectangle.setPosition(MAP_X_COORD + i * rectangleSize + outlineTricknesSize, MAP_Y_COORD + j * rectangleSize + outlineTricknesSize);
            window.draw(rectangle);
        }
    }

    std::string str = "Поколение: " + std::to_string(era);
    sfString.setPosition(15, 15);
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    window.draw(sfString);
    int deqPos = 1;
    sfString.setCharacterSize(15);
    for (auto i : scores)
    {
        sfString.setString(std::to_string(i.first) + ": " + std::to_string(i.second));
        sfString.setPosition(15, 50 + deqPos++ * 25);
        window.draw(sfString);
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
        switch (event.type)
        {
        case sf::Event::Closed:
            CloseWindow();
            result.emplace_back(Event::CLOSE);
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                result.emplace_back(Event::PAUSE);
            }
        default:
            break;
        }
    }

    return result;
}

void Graphics::getNewScore(int era, int score)
{
    scores.push_front(std::make_pair(era, score));
    if (scores.size() > 20)
    {
        scores.pop_back();
    }
}