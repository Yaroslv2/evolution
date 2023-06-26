#include "../headers/menu_page.h"

#define BUTTONS_COUNT 4

MenuPage::MenuPage(sf::RenderWindow *&w, WindowState *&s, sf::Font *&f, float width, float height)
    : Page(w, s, f, width, height), activeButton(Buttons::START)
{
    text.setFont(*font);
    text.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(300, 60));
}

MenuPage::~MenuPage() {}

void MenuPage::update()
{
    processEvents();

    draw();
}

void MenuPage::processEvents()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                switch (activeButton)
                {
                case MenuPage::Buttons::START:
                    state->setState(WindowState::State::EVOLUTION);
                    break;
                case MenuPage::Buttons::SETTINGS:
                    state->setState(WindowState::State::SETTINGS);
                    break;
                case MenuPage::Buttons::INFO:
                    state->setState(WindowState::State::INFO);
                    break;
                case MenuPage::Buttons::EXIT:
                    state->setState(WindowState::State::CLOSE);
                    break;
                default:
                    break;
                }
                break;
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            }
        default:
            break;
        }
    }
}

void MenuPage::draw()
{
    window->clear();
    std::string str = "ЭВОЛЮЦИЯ";
    text.setCharacterSize(100);
    text.setPosition(width / 2 - 100 - (text.getLocalBounds().width / 2), height * 0.25 - text.getLocalBounds().height / 2);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    window->draw(text);
    text.setCharacterSize(35);
    drawButton("НАЧАТЬ", width / 2, height * 0.5, activeButton == Buttons::START ? sf::Color::White : sf::Color::Black);
    drawButton("НАСТРОЙКИ", width / 2, height * 0.5 + 100, activeButton == Buttons::SETTINGS ? sf::Color::White : sf::Color::Black);
    drawButton("СПРАВКА", width / 2, height * 0.5 + 200, activeButton == Buttons::INFO ? sf::Color::White : sf::Color::Black);
    drawButton("ВЫХОД", width / 2, height * 0.5 + 300, activeButton == Buttons::EXIT ? sf::Color::White : sf::Color::Black);

    window->display();
}

void MenuPage::drawButton(std::string str, float x, float y, sf::Color color)
{
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(x - text.getLocalBounds().width / 2, y - rectangle.getLocalBounds().height * 0.4);
    rectangle.setPosition(x - rectangle.getLocalBounds().width / 2, y - rectangle.getLocalBounds().height / 2);
    rectangle.setFillColor(color);
    window->draw(rectangle);
    if (color == sf::Color::Black)
    {
        text.setFillColor(sf::Color::White);
    }
    else
    {
        text.setFillColor(sf::Color::Black);
    }
    window->draw(text);
}

void MenuPage::moveUp()
{
    int b = (int)activeButton;
    if (--b < 0)
    {
        b = BUTTONS_COUNT - 1;
    }
    activeButton = (Buttons)b;
}

void MenuPage::moveDown()
{
    int b = (int)activeButton;
    if (++b >= BUTTONS_COUNT)
    {
        b = 0;
    }
    activeButton = (Buttons)b;
}