#include "../headers/loading_app_page.h"
#include <string>

LoadingAppPage::LoadingAppPage(sf::RenderWindow *&w, WindowState *&s, sf::Font *&f, float width, float height)
    : Page(w, s, f, width, height)
{
    text.setFont(*font);
    text.setFillColor(sf::Color::White);
}

LoadingAppPage::~LoadingAppPage() {}

void LoadingAppPage::update()
{
    processEvents();

    draw();
}

void LoadingAppPage::processEvents()
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
        }
    }
}

void LoadingAppPage::draw()
{
    window->clear();

    text.setCharacterSize(140);
    std::string str = "ЭВОЛЮЦИЯ";
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(sf::Vector2f((width / 2) - text.getLocalBounds().width / 2, (height * 0.4) - text.getLocalBounds().height / 2));
    window->draw(text);
    text.setCharacterSize(30);
    str = "Мудров Ярослав О722Б";
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(sf::Vector2f((width / 2) - text.getLocalBounds().width / 2, (height * 0.5) - text.getLocalBounds().height / 2));
    window->draw(text);
    text.setCharacterSize(15);
    str = "Для продолжения нажмите любую клавишу. Кроме кнопки питания.";
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(sf::Vector2f((width / 2) - text.getLocalBounds().width / 2, (height * 0.75) - text.getLocalBounds().height / 2));
    window->draw(text);
    window->display();
}