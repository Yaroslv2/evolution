#include "../headers/settings_page.h"
#include <string>

#define COLORS_COUNT 5

SettingsPage::SettingsPage(sf::RenderWindow *&w, WindowState *&s, sf::Font *&f, float width, float height, sf::Color *&c)
    : Page(w, s, f, width, height), savedColor(c)
{
    colors.resize(COLORS_COUNT);
    text.setFont(*font);
    text.setFillColor(sf::Color::White);
    colors[0] = sf::Color::Blue;
    colors[1] = sf::Color(139, 0, 115);
    colors[2] = sf::Color(0, 131, 115);
    colors[3] = sf::Color(204, 0, 204);
    colors[4] = sf::Color(204, 0, 102);
    for (int i = 0; i < COLORS_COUNT; i++)
    {
        if (colors[i] == *c)
            activeColorIdx = i;
    }
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(5);
}

SettingsPage::~SettingsPage() {}

void SettingsPage::update()
{
    processEvents();

    draw();
}

void SettingsPage::processEvents()
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
                *savedColor = colors[activeColorIdx];
                state->setState(WindowState::State::MENU);
                break;
            case sf::Keyboard::Escape:
                for (int i = 0; i < COLORS_COUNT; i++)
                {
                    if (colors[i] == *savedColor)
                    {
                        activeColorIdx = i;
                    }
                }
                state->setState(WindowState::State::MENU);
                break;
            case sf::Keyboard::Left:
                moveLeft();
                break;
            case sf::Keyboard::Right:
                moveRight();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void SettingsPage::draw()
{
    window->clear();

    rectangle.setSize(sf::Vector2f(200, 200));
    rectangle.setFillColor(colors[activeColorIdx]);
    rectangle.setPosition(width / 2 - rectangle.getLocalBounds().width / 2, height * 0.5 - rectangle.getLocalBounds().height / 2);
    window->draw(rectangle);
    rectangle.setSize(sf::Vector2f(65, 65));
    rectangle.setOutlineColor(sf::Color::Black);
    float xpos = width * 0.42, step = 75;
    for (int i = 0; i < COLORS_COUNT; i++)
    {
        rectangle.setFillColor(colors[i]);
        rectangle.setPosition(xpos - rectangle.getLocalBounds().width / 2, height * 0.7 - rectangle.getLocalBounds().height / 2);
        if (i == activeColorIdx)
        {
            rectangle.setOutlineColor(sf::Color(160, 160, 160));
        }
        window->draw(rectangle);
        if (i == activeColorIdx)
            rectangle.setOutlineColor(sf::Color::Black);
        xpos += step;
    }
    std::string str = "НАСТРОЙКИ";
    text.setCharacterSize(90);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(width / 2 - text.getLocalBounds().width / 2, height * 0.2 - text.getLocalBounds().height / 2);
    window->draw(text);
    str = "Выбор цвета бота";
    text.setCharacterSize(40);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(width / 2 - text.getLocalBounds().width / 2, height * 0.3 - text.getLocalBounds().height / 2);
    window->draw(text);
    str = "Для выхода без сохранения нажмите Esc. Чтобы подтвердить сохранение нажмите Enter.";
    text.setCharacterSize(20);
    text.setString(sf::String::fromUtf8(str.begin(), str.end()));
    text.setPosition(width / 2 - text.getLocalBounds().width / 2, height * 0.8 - text.getLocalBounds().height / 2);
    window->draw(text);
    window->display();
}

void SettingsPage::moveLeft()
{
    if (--activeColorIdx < 0)
    {
        activeColorIdx = COLORS_COUNT - 1;
    }
}

void SettingsPage::moveRight()
{
    if (++activeColorIdx >= COLORS_COUNT)
    {
        activeColorIdx = 0;
    }
}