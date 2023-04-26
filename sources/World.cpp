#include "../headers/World.h"

#define FEED_HEALTH 5
#define POISON_HEALTH 5
#define BOTS_COUNT 64
#define EAT_COUNT 40
#define POISON_COUNT 30
#define WALL_COUNT 10
#define BOT_DOWN_LIMIT 8

World::World() {}

World::World(int n, int m) : n(n), m(m)
{
    score = 0;
    pole.resize(n);
    for (int i = 0; i < n; i++)
    {
        pole[i].resize(m);
    }
    Reset();
    FillObject<Bot>(BOTS_COUNT);
    reloadBotCoords();
}

void World::Reset()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            pole[i][j] = new Empty();
        }
    }
    FillObject<Eat>(EAT_COUNT);
    FillObject<Poison>(POISON_COUNT);
    FillObject<Wall>(WALL_COUNT);
}

template <class T>
void World::FillObject(int count)
{
    std::set<std::pair<int, int>> s;
    while (s.size() < count)
    {
        std::pair<int, int> coord = std::make_pair(rand() % n, rand() % m);
        if (pole[coord.first][coord.second]->GetType() == Object::Type::EMPTY)
        {
            s.insert(coord);
        }
    }
    for (auto i : s)
    {
        delete pole[i.first][i.second];
        pole[i.first][i.second] = new T();
    }
}

void World::MakeTurn()
{
    int count = botsCoord.size();
    for (int i = 0; i < count; i++)
    {
        std::pair<int, int> botCoord = botsCoord.front();
        botsCoord.pop();
        Bot *bot = (Bot *)pole[botCoord.first][botCoord.second];
        std::pair<int, int> newCoords = botCoord;
        Object::Type arg = Object::Type::NUN;
        for (int i = 0; i < 10; i++)
        {
            score++;
            Bot::Action action = bot->MakeAction(arg);
            switch (action)
            {
            case Bot::Action::GO:
                newCoords = ProcessDirection(botCoord, bot);
                botCoord = ChangeBotCoords(botCoord, newCoords, bot);
                break;
            case Bot::Action::EAT:
                newCoords = ProcessDirection(botCoord, bot);
                if (IsInPole(newCoords))
                {
                    switch (pole[newCoords.first][newCoords.second]->GetType())
                    {
                    case Object::Type::EAT:
                        bot->Feed(FEED_HEALTH);
                        break;
                    case Object::Type::POISON:
                        bot->Poison(POISON_HEALTH);
                        break;
                    default:
                        break;
                    }
                }
                break;
            case Bot::Action::CONVERT:
                newCoords = ProcessDirection(botCoord, bot);
                if (IsInPole(newCoords))
                {
                    if (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::POISON)
                    {
                        delete pole[newCoords.first][newCoords.second];
                        pole[newCoords.first][newCoords.second] = new Eat();
                    }
                }
                break;
            case Bot::Action::LOOK:
                newCoords = ProcessDirection(botCoord, bot);
                if (!IsInPole(newCoords))
                {
                    arg = Object::Type::NUN;
                }
                else
                {
                    arg = pole[newCoords.first][newCoords.second]->GetType();
                }
                break;
            }
            bot->Poison(1);
            if (bot->GetHealth() <= 0)
                break;
        }
        if (bot->GetHealth() <= 0)
        {
            cemetery.push_front(bot);
            pole[botCoord.first][botCoord.second] = new Empty();
            deleteFromCemetery(8);
        }
        else
            botsCoord.push(botCoord);
    }
}

const std::vector<std::vector<Object *>> &World::getPole()
{
    return pole;
}

std::pair<int, int> World::ChangeBotCoords(std::pair<int, int> botCoords, std::pair<int, int> newCoords, Bot *&bot)
{
    if (!IsInPole(newCoords) || (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::WALL) || (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::BOT))
        return botCoords;

    switch (pole[newCoords.first][newCoords.second]->GetType())
    {
    case Object::Type::EAT:
        bot->Feed(FEED_HEALTH / 2);
        delete pole[newCoords.first][newCoords.second];
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    case Object::Type::POISON:
        bot->Poison(POISON_HEALTH / 2);
        delete pole[newCoords.first][newCoords.second];
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    default:
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    }

    return newCoords;
}

bool World::IsInPole(std::pair<int, int> coord)
{
    if (coord.first < 0 || coord.second < 0 || coord.first >= n || coord.second >= m)
        return false;
    return true;
}

std::pair<int, int> World::ProcessDirection(std::pair<int, int> botCoord, Bot *&bot)
{
    Bot::Direction direction = bot->GetDirection();
    switch (direction)
    {
    case Bot::Direction::UP_LEFT:
        botCoord.first--;
        botCoord.second++;
        break;
    case Bot::Direction::UP:
        botCoord.second++;
        break;
    case Bot::Direction::UP_RIGHT:
        botCoord.first++;
        botCoord.second++;
        break;
    case Bot::Direction::RIGHT:
        botCoord.first++;
        break;
    case Bot::Direction::DOWN_RIGHT:
        botCoord.first++;
        botCoord.second--;
        break;
    case Bot::Direction::DOWN:
        botCoord.second--;
        break;
    case Bot::Direction::DOWN_LEFT:
        botCoord.first--;
        botCoord.second--;
        break;
    case Bot::Direction::LEFT:
        botCoord.first--;
        break;
    }
    return botCoord;
}

bool World::needEvolve()
{
    return botsCoord.size() <= BOT_DOWN_LIMIT;
}

void World::Evolve()
{
    score = 0;
    std::vector<Bot *> bots;
    std::pair<int, int> coord;
    while (!botsCoord.empty())
    {
        coord = botsCoord.front();
        botsCoord.pop();
        bots.push_back((Bot *)pole[coord.first][coord.second]);
        bots.back()->reset();
    }
    Reset();
    while (bots.size() < BOT_DOWN_LIMIT)
    {
        Bot *bot = cemetery.front();
        bots.push_back(bot);
        bots.back()->reset();
    }
    deleteFromCemetery(0);

    for (int i = 0; i < BOT_DOWN_LIMIT; i++)
    {
        for (int j = 0; j < BOT_DOWN_LIMIT; j++)
        {
            bots.push_back(new Bot(*bots[i]));
        }
    }
    std::set<int> s;
    while (s.size() < 10)
    {
        s.insert(rand() % bots.size());
    }
    for (auto i : s)
    {
        bots[i]->evolve(8);
    }
    for (int i = 0; i < bots.size(); i++)
    {
        insertObject(bots[i]);
    }
    reloadBotCoords();
}

void World::reloadBotCoords()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (pole[i][j]->GetType() == Object::Type::BOT)
            {
                
                botsCoord.push(std::make_pair(i, j));
            }
        }
    }
}

void World::insertObject(Object *obj)
{
    std::pair<int, int> coord;
    do
    {
        coord = std::make_pair(rand() % n, rand() % m);
    } while (pole[coord.first][coord.second]->GetType() != Object::Type::EMPTY);
    delete pole[coord.first][coord.second];
    pole[coord.first][coord.second] = obj;
}

void World::deleteFromCemetery(int size)
{
    while (cemetery.size() > size)
    {
        cemetery.pop_back();
    }
}