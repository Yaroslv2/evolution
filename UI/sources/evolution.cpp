#include "../headers/evolution.h"

#define SPEED_TIME_DELTA 2401
#define MAP_X_COORD 350
#define MAP_Y_COORD 105

EvolutionPage::EvolutionPage(sf::RenderWindow *&w, WindowState *&s, sf::Font *&f, float wid, float h)
    : pause(false), needDraw(true), era(1), speed(2401), rectangleSize(30), outlineTricknesSize(3), average(0), width(wid), height(h)
{
    window = w;
    state = s;
    font = *f;
    rectangle.setSize(sf::Vector2f(rectangleSize, rectangleSize));
    rectangle.setOutlineColor(sf::Color(160, 160, 160));
    rectangle.setOutlineThickness(outlineTricknesSize);
    sfString.setFont(font);
    sfString.setFillColor(sf::Color::White);
    optionsRectangle.setOutlineColor(sf::Color::White);
    optionsRectangle.setOutlineThickness(5);
    optionsRectangle.setFillColor(sf::Color::Black);
}

EvolutionPage::~EvolutionPage() {}

void EvolutionPage::start(sf::Color color)
{
    botsColor = color;
    era = 1;
    speed = 7;
    needDraw = true;
    pause = false;
    World world;
    while (state->getState() == WindowState::State::EVOLUTION)
    {
        for (int i = 0; i < speed; i++)
            processingEvents();
        if (world.needEvolve()) // check is it necessary to create a new generation
        {
            getNewScore(era++, world.score); // save generation`s score
            world.evolve();                  // create new generation
        }
        if (!pause) // pause algorithm or not
        {
            world.makeTurn(); // actions of bots
        }
        if (needDraw)
            draw(world.getPole());
    }
    scores.clear();
}

void EvolutionPage::processingEvents()
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
            case sf::Keyboard::Key::Escape:
                state->setState(WindowState::State::MENU);
                break;
            case sf::Keyboard::Key::Space:
                pause = !pause;
                break;
            case sf::Keyboard::Key::Z:
                speed /= SPEED_TIME_DELTA;
                if (speed == 0)
                    speed = 1;
                break;
            case sf::Keyboard::Key::X:
                speed *= SPEED_TIME_DELTA;
                if (speed > 16807)
                    speed = 16807;
                break;
            case sf::Keyboard::Key::S:
                needDraw = !needDraw;
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

void EvolutionPage::draw(const std::vector<std::vector<Object *>> &pole)
{
    window->clear();
    // draw map
    Bot *bot;
    for (int i = 0; i < pole.size(); i++)
    {
        for (int j = 0; j < pole[i].size(); j++)
        {
            switch (pole[i][j]->GetType())
            {
            case Object::Type::BOT:
                rectangle.setFillColor(botsColor);
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
            window->draw(rectangle);
            if (pole[i][j]->GetType() == Object::Type::BOT)
                window->draw(sfString);
        }
    }

    optionsRectangle.setSize(sf::Vector2f(width * 0.15, height * 0.58));
    optionsRectangle.setPosition(width * 0.01, height * 0.08);
    window->draw(optionsRectangle);
    // draw generation
    std::string str = "Поколение: " + std::to_string(era);
    sfString.setPosition(width * 0.02, height * 0.1);
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    window->draw(sfString);
    // draw scores previos generations
    int deqPos = 1;
    sfString.setCharacterSize(15);
    for (auto i : scores)
    {
        sfString.setString(std::to_string(i.first) + ": " + std::to_string(i.second));
        sfString.setPosition(width * 0.02, height * 0.12 + deqPos++ * 25);
        window->draw(sfString);
    }

    str = "Средний счет: " + std::to_string(average);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.02, height * 0.63);
    window->draw(sfString);

    optionsRectangle.setSize(sf::Vector2f(width * 0.15, height * 0.3));
    optionsRectangle.setPosition(width * 0.83, height * 0.09);
    rectangle.setFillColor(botsColor);
    rectangle.setPosition(width * 0.84, height * 0.12);
    window->draw(optionsRectangle);
    window->draw(rectangle);
    str = "бот";
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.87, height * 0.115);
    window->draw(sfString);

    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(width * 0.84, height * 0.17);
    window->draw(rectangle);
    str = "еда";
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.87, height * 0.165);
    window->draw(sfString);

    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(width * 0.84, height * 0.22);
    window->draw(rectangle);
    str = "яд";
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.87, height * 0.215);
    window->draw(sfString);
    rectangle.setFillColor(sf::Color(160, 160, 160));
    rectangle.setPosition(width * 0.84, height * 0.27);
    window->draw(rectangle);
    str = "стена";
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.87, height * 0.265);
    window->draw(sfString);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(width * 0.84, height * 0.32);
    window->draw(rectangle);
    str = "пустота";
    sfString.setCharacterSize(30);
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.87, height * 0.315);
    window->draw(sfString);

    optionsRectangle.setSize(sf::Vector2f(width * 0.7, height * 0.25));
    optionsRectangle.setPosition(width * 0.5 - optionsRectangle.getLocalBounds().width / 2, height * 0.83 - optionsRectangle.getLocalBounds().height / 2);
    window->draw(optionsRectangle);
    sfString.setCharacterSize(40);
    str = "SPACE - пауза";
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.18, height * 0.73);
    window->draw(sfString);
    str = "S - переключение отрисовки";
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.18, height * 0.8);
    window->draw(sfString);
    str = "ESC - выход";
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.18, height * 0.87);
    window->draw(sfString);
    str = "Z - ускорение";
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.6, height * 0.73);
    window->draw(sfString);
    str = "X - замедление";
    sfString.setString(sf::String::fromUtf8(str.begin(), str.end()));
    sfString.setPosition(width * 0.6, height * 0.8);
    window->draw(sfString);
    window->display();
}

void EvolutionPage::getNewScore(int era, int score)
{
    average = (average + score) / 2;
    scores.push_front(std::make_pair(era, score));
    while (scores.size() > 20)
    {
        scores.pop_back();
    }
}