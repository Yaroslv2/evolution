#include "../headers/info_page.h"
#include <iostream>
#include <string>

#define MAP_SIZE 15

InfoPage::InfoPage(sf::RenderWindow *&w, WindowState *&s, sf::Font *&f, float width, float height)
    : Page(w, s, f, width, height)
{
    text.setFont(*font);
    text.setFillColor(sf::Color::White);
    infoFile.open("assets/info/info.txt");
    if (!infoFile.is_open())
    {
        std::cout << "Не удалось открыть файл" << std::endl;
        exit(EXIT_FAILURE);
    }

    map.resize(MAP_SIZE);
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i].resize(MAP_SIZE);
        for (int j = 0; j < MAP_SIZE; j++) {
            int randColor = rand() % 5;
            switch (randColor)
            {
            case 0:
                map[i][j] = sf::Color::Black;
                break;
            case 1:
                map[i][j] = sf::Color::Blue;
                break;
            case 2:
                map[i][j] = sf::Color::Green;
                break;
            case 3:
                map[i][j] = sf::Color::Red;
                break;
            case 4:
                map[i][j] = sf::Color(160, 160, 160);
                break;
            default:
                break;
            }
        }
    }
}

InfoPage::~InfoPage() {}

void InfoPage::update()
{
    processEvents();
    draw();
}

void InfoPage::processEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            state->setState(WindowState::State::CLOSE);
            break;
        case sf::Event::KeyReleased:
            state->setState(WindowState::State::MENU);
            break;
        default:
            break;
        }
    }
}

void InfoPage::draw()
{
    window->clear();

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setSize(sf::Vector2f(width * 0.6, height * 0.85));
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setPosition(width * 0.33 - rectangle.getLocalBounds().width / 2, height / 2 - rectangle.getLocalBounds().height / 2);
    window->draw(rectangle);

    std::string str;
    text.setCharacterSize(28);
    int step = 40, ypos = height / 2 - rectangle.getLocalBounds().height / 2 + 5;
    while (getline(infoFile, str))
    {
        text.setString(sf::String::fromUtf8(str.begin(), str.end()));
        text.setPosition(width * 0.35 - rectangle.getLocalBounds().width / 2, ypos += step);
        window->draw(text);
    }

    text.setCharacterSize(100);
    str = "СПРАВКА";
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(width * 0.7, height / 2 - rectangle.getLocalBounds().height / 2);
    window->draw(text);

    int rectangleSize = 30, outlineTricknesSize = 3;

    rectangle.setSize(sf::Vector2f(rectangleSize, rectangleSize));
    rectangle.setOutlineThickness(outlineTricknesSize);
    rectangle.setOutlineColor(sf::Color(160, 160, 160));

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            rectangle.setFillColor(map[i][j]);
            rectangle.setPosition(width * 0.7 + i * rectangleSize + outlineTricknesSize, height * 0.3 + j * rectangleSize + outlineTricknesSize);
            window->draw(rectangle);
        }
    }

    text.setCharacterSize(20);
    str = "Для продолжения нажмите любую кнопку.";
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(width * 0.71, height * 0.9);
    window->draw(text);
    window->display();
    infoFile.clear();
    infoFile.seekg(0);
}