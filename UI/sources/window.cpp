#include "../headers/window.h"
#include <iostream>

#define FONT_FILE "/home/onefore/projects/course-paper/assets/Roboto/Roboto-Bold.ttf"

Window::Window()
{
    state = new WindowState();
    window = new sf::RenderWindow;
    window->create(sf::VideoMode::getDesktopMode(), "Evolution", sf::Style::Fullscreen);
    window->setFramerateLimit(60);
    font = new sf::Font;
    if (!(font->loadFromFile(FONT_FILE)))
    {
        std::cout << "Error: cannot load font from file" << std::endl;
        exit(EXIT_FAILURE);
    }
    *botsColor = sf::Color::Blue;
    width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
    height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    loadingAppPage = new LoadingAppPage(window, state, font, width, height);
    menuPage = new MenuPage(window, state, font, width, height);
    settingsPage = new SettingsPage(window, state, font, width, height, botsColor);
    evolutionPage = new EvolutionPage(window, state, font, width, height);
    infoPage = new InfoPage(window, state, font, width, height);
}

Window::~Window()
{
    delete loadingAppPage;
    delete menuPage;
    delete settingsPage;
    delete evolutionPage;
    delete state;
    delete window;
}

void Window::start()
{
    while (window->isOpen())
    {
        switch (state->getState())
        {
        case WindowState::State::LOADING_APP:
            loadingAppPage->update();
            break;
        case WindowState::State::MENU:
            menuPage->update();
            break;
        case WindowState::State::EVOLUTION:
            evolutionPage->start(*botsColor);
            break;
        case WindowState::State::SETTINGS:
            settingsPage->update();
            break;
        case WindowState::State::INFO:
            infoPage->update();
            break;
        case WindowState::State::CLOSE:
            window->close();
            break;
        }
    }
}