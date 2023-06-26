#include "../headers/World.h"

#define FEED_HEALTH 5
#define POISON_HEALTH 5
#define BOTS_COUNT 64
#define EAT_COUNT 240
#define POISON_COUNT 270
#define WALL_COUNT 120
#define BOT_DOWN_LIMIT 8
#define EAT_DOWN_LIMIT 60
#define POISON_DOWN_LIMIT 70

World::World() : n(40), m(20), eatOnMapCount(EAT_COUNT), poisonOnMapCount(POISON_COUNT)
{
    score = 0;
    pole.resize(n);
    for (int i = 0; i < n; i++)
    {
        pole[i].resize(m);
    }
    reset();                     // fill map of objects
    fillObject<Bot>(BOTS_COUNT); // set bots on map
    reloadBotCoords();           // save bots coodinates
}

void World::reset()
{
    // get empty map
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            pole[i][j] = new Empty();
        }
    }
    fillObject<Eat>(EAT_COUNT);       // set eat on map
    fillObject<Poison>(POISON_COUNT); // set poison on map
    fillObject<Wall>(WALL_COUNT);     // set walls on map

    while (!feedCoord.empty())
    {
        feedCoord.pop();
    }
    while (!poisonCoord.empty())
    {
        poisonCoord.pop();
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (pole[i][j]->GetType() == Object::Type::EAT)
                feedCoord.push({i, j});
            else if (pole[i][j]->GetType() == Object::Type::POISON)
                poisonCoord.push({i, j});
        }
    }
    eatOnMapCount = EAT_COUNT;
    poisonOnMapCount = POISON_COUNT;
}

template <class T>
void World::fillObject(int count)
{
    std::set<std::pair<int, int>> s; // unique empty coordinates
    // generate coordinates
    while (s.size() < count)
    {
        std::pair<int, int> coord = std::make_pair(rand() % n, rand() % m);
        if (pole[coord.first][coord.second]->GetType() == Object::Type::EMPTY) // insert coordinates if this is coordinates of empty place
        {
            s.insert(coord);
        }
    }
    for (auto i : s) // set object on new coords
    {
        delete pole[i.first][i.second];
        pole[i.first][i.second] = new T();
    }
}

// bots actions
void World::makeTurn()
{
    int count = botsCoord.size();
    for (int i = 0; i < count; i++)
    {
        std::pair<int, int> botCoord = botsCoord.front();
        botsCoord.pop();
        Bot *bot = (Bot *)pole[botCoord.first][botCoord.second];
        std::pair<int, int> newCoords = botCoord;
        bool needBreak = false;
        Object::Type arg = Object::Type::NUN; // return of bot LOOK action
        for (int i = 0; i < 10; i++)
        {
            Bot::Action action = bot->MakeAction(arg); // get command of bot
            switch (action)
            {
            case Bot::Action::GO:
                newCoords = processDirection(botCoord, (int)bot->GetDirection()); // return coordinates front of bot
                botCoord = changeBotCoords(botCoord, newCoords, bot);
                needBreak = true;
                break;
            case Bot::Action::EAT:
                newCoords = processDirection(botCoord, (int)bot->GetDirection());
                if (isInPole(newCoords))
                {
                    switch (pole[newCoords.first][newCoords.second]->GetType())
                    {
                    case Object::Type::EAT:
                        bot->Feed(FEED_HEALTH);
                        delete pole[newCoords.first][newCoords.second];
                        pole[newCoords.first][newCoords.second] = new Empty();
                        eatOnMapCount--;
                        break;
                    case Object::Type::POISON:
                        bot->Poison(POISON_HEALTH);
                        delete pole[newCoords.first][newCoords.second];
                        pole[newCoords.first][newCoords.second] = new Empty();
                        poisonOnMapCount--;
                        break;
                    default:
                        break;
                    }
                }
                needBreak = true;
                break;
            case Bot::Action::CONVERT:
                newCoords = processDirection(botCoord, (int)bot->GetDirection());
                if (isInPole(newCoords))
                {
                    if (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::POISON)
                    {
                        delete pole[newCoords.first][newCoords.second];
                        pole[newCoords.first][newCoords.second] = new Eat();
                        poisonOnMapCount--;
                        eatOnMapCount++;
                    }
                }
                needBreak = true;
                break;
            case Bot::Action::LOOK:
                newCoords = processDirection(botCoord, (int)bot->GetDirection());
                if (!isInPole(newCoords))
                {
                    arg = Object::Type::NUN;
                }
                else
                {
                    arg = pole[newCoords.first][newCoords.second]->GetType();
                }
                break;
            }
            if (bot->GetHealth() <= 0 || needBreak)
                break;
        }
        score++;
        bot->Poison(1);
        // delete bot from map when it is dead
        if (bot->GetHealth() <= 0)
        {
            cemetery.push_front(bot);
            pole[botCoord.first][botCoord.second] = new Empty();
            deleteFromCemetery(8);
        }
        else
            botsCoord.push(botCoord);
    }
    poisonRegenerate();
    feadRegenerate();
}

const std::vector<std::vector<Object *>> &World::getPole()
{
    return pole;
}

std::pair<int, int> World::changeBotCoords(std::pair<int, int> botCoords, std::pair<int, int> newCoords, Bot *&bot)
{
    if (!isInPole(newCoords) || (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::WALL) || (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::BOT))
        return botCoords;

    switch (pole[newCoords.first][newCoords.second]->GetType())
    {
    case Object::Type::EAT:
        bot->Feed(FEED_HEALTH / 2);
        eatOnMapCount--;
        delete pole[newCoords.first][newCoords.second];
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    case Object::Type::POISON:
        bot->Poison(POISON_HEALTH / 2);
        poisonOnMapCount--;
        delete pole[newCoords.first][newCoords.second];
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    default:
        delete pole[newCoords.first][newCoords.second];
        pole[newCoords.first][newCoords.second] = bot;
        pole[botCoords.first][botCoords.second] = new Empty();
        break;
    }

    return newCoords;
}

bool World::isInPole(std::pair<int, int> coord)
{
    if (coord.first < 0 || coord.second < 0 || coord.first >= n || coord.second >= m)
        return false;
    return true;
}

std::pair<int, int> World::processDirection(std::pair<int, int> botCoord, int direction)
{
    switch (direction)
    {
    case 0:
        botCoord.first--;
        botCoord.second++;
        break;
    case 1:
        botCoord.second++;
        break;
    case 2:
        botCoord.first++;
        botCoord.second++;
        break;
    case 3:
        botCoord.first++;
        break;
    case 4:
        botCoord.first++;
        botCoord.second--;
        break;
    case 5:
        botCoord.second--;
        break;
    case 6:
        botCoord.first--;
        botCoord.second--;
        break;
    case 7:
        botCoord.first--;
        break;
    }
    return botCoord;
}

bool World::needEvolve()
{
    return botsCoord.size() <= BOT_DOWN_LIMIT;
}

void World::evolve()
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
    reset();
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

void World::feadRegenerate()
{
    while (eatOnMapCount <= EAT_DOWN_LIMIT)
    {
        std::pair<int, int> coords;
        do
        {
            coords = feedCoord.front();
            feedCoord.pop();
        } while (pole[coords.first][coords.second]->GetType() != Object::Type::EAT && !feedCoord.empty());
        for (int direction = 0; direction < DIRECTION_COUNT; direction++)
        {
            std::pair<int, int> newCoords = processDirection(coords, direction);
            if (isInPole(newCoords) && pole[newCoords.first][newCoords.second]->GetType() == Object::Type::EMPTY)
            {
                delete pole[newCoords.first][newCoords.second];
                pole[newCoords.first][newCoords.second] = new Eat();
                eatOnMapCount++;
                feedCoord.push(newCoords);
                break;
            }
        }
        feedCoord.push(coords);
    }
}

void World::poisonRegenerate()
{
    while (poisonOnMapCount <= POISON_DOWN_LIMIT)
    {
        std::pair<int, int> coords;
        do
        {
            coords = poisonCoord.front();
            poisonCoord.pop();
        } while (pole[coords.first][coords.second]->GetType() != Object::Type::POISON && !poisonCoord.empty());
        for (int direction = 0; direction < DIRECTION_COUNT; direction++)
        {
            std::pair<int, int> newCoords = processDirection(coords, direction);
            if (isInPole(newCoords) && (pole[newCoords.first][newCoords.second]->GetType() == Object::Type::EMPTY || pole[newCoords.first][newCoords.second]->GetType() == Object::Type::EAT))
            {
                delete pole[newCoords.first][newCoords.second];
                pole[newCoords.first][newCoords.second] = new Poison();
                poisonOnMapCount++;
                poisonCoord.push(newCoords);
                break;
            }
        }
        poisonCoord.push(coords);
    }
}