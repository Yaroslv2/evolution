#include "../headers/Graphics.h"
#include <iostream>
#include <string>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 1500
#define MAP_X_COORD 300
#define MAP_Y_COORD 100

#define FONT_FILE "/home/onefore/projects/course-paper/assets/Roboto/Roboto-Bold.ttf"

Graphics::Graphics() : rectangleSize(30), outlineTricknesSize(2)
{
    window.create(sf::VideoMode(1500, 700), "Evolution");
    view = window.getDefaultView();
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
    // draw map
    Bot *bot;
    for (int i = 0; i < pole.size(); i++)
    {
        for (int j = 0; j < pole[i].size(); j++)
        {
            switch (pole[i][j]->GetType())
            {
            case Object::Type::BOT:
                rectangle.setFillColor(sf::Color::Blue);
                bot = static_cast<Bot *>(pole[i][j]);
                sfString.setString(std::to_string(bot->GetHealth()));
                sfString.setCharacterSize(15);
                sfString.setPosition(MAP_X_COORD + i * rectangleSize + outlineTricknesSize + 5, 5 + MAP_Y_COORD + j * rectangleSize + outlineTricknesSize);
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
            if (pole[i][j]->GetType() == Object::Type::BOT)
                window.draw(sfString);
        }
    }

    // draw generation
    std::string str = "Поколение: " + std::to_string(era);
    sfString.setPosition(15, 15);
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    window.draw(sfString);

    // draw scores previos generations
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
    while (window.pollEvent(event)) // processing events
    {
        switch (event.type)
        {
        case sf::Event::Closed: // close window
            CloseWindow();
            result.emplace_back(Event::CLOSE);
            break;
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Key::Space:
                result.emplace_back(Event::PAUSE);
                break;
            case sf::Keyboard::Key::Z:
                result.emplace_back(Event::DECREASE_SPEED);
                break;
            case sf::Keyboard::Key::X:
                result.emplace_back(Event::INCREASE_SPEED);
                break;
            case sf::Keyboard::Key::S:
                result.emplace_back(Event::SWITCH_DRAW);
                break;
            default:
                break;
            }
            break;
        case sf::Event::Resized:
            view.setSize({static_cast<float>(event.size.width),
                          static_cast<float>(event.size.height)});
            window.setView(view);
            break;
        default:
            break;
        }
    }

    return result;
}

void Graphics::getNewScore(int era, int score)
{
    scores.push_front(std::make_pair(era, score));
    while (scores.size() > 20)
    {
        scores.pop_back();
    }
}