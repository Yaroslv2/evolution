#include "../headers/Bot.h"
#include <set>

Bot::Bot() : Object(Object::Type::BOT), // set object type
             health(MAX_HEALTH),
             direction((Bot::Direction)(std::rand() % DIRECTION_COUNT)), // set direction of bot
             curCommand(0)
{
    for (int i = 0; i < GENOM_SIZE; i++) // generate genom
    {
        genom.push_back(GenerateCommand());
    }
}

Bot::Bot(const Bot &bot) : Object(Object::Type::BOT),
                           health(MAX_HEALTH),
                           direction((Bot::Direction)(std::rand() % DIRECTION_COUNT)),
                           curCommand(0),
                           genom(bot.genom)
{
}

int Bot::GetHealth()
{
    return health;
}

// bot feed
void Bot::Feed(int feed_health)
{
    health += feed_health;
    health %= MAX_HEALTH;
}

// poison bot
void Bot::Poison(int poison_health)
{
    health -= poison_health;
}

Bot::Command Bot::GenerateCommand()
{
    return (Bot::Command)(std::rand() % COMMAND_COUNT);
}

// bot action
Bot::Action Bot::MakeAction(Object::Type type)
{
    Bot::Action result = Bot::Action::VOID;

    // if previos command was BOT::ACTION::LOOK
    if (type != Object::Type::NUN)
    {
        curCommand = (curCommand + (int)type - 1) % GENOM_SIZE;
    }

    // proccess command
    switch (genom[curCommand])
    {
    case Bot::Command::GO:
        result = Bot::Action::GO;
        break;
    case Bot::Command::TURN_LEFT:
        direction = (Bot::Direction)(((int)direction - 1) % DIRECTION_COUNT);
        break;
    case Bot::Command::TURN_RIGHT:
        direction = (Bot::Direction)(((int)direction + 1) % DIRECTION_COUNT);
        break;
    case Bot::Command::EAT:
        result = Bot::Action::EAT;
        break;
    case Bot::Command::LOOK:
        result = Bot::Action::LOOK;
        break;
    case Bot::Command::CONVERT:
        result = Bot::Action::CONVERT;
    default:
        break;
    }

    ++curCommand %= GENOM_SIZE;

    return result;
}

Bot::Direction Bot::GetDirection()
{
    return direction;
}

// bot evolution
void Bot::evolve(int mutatuionCount)
{
    std::set<int> mutations;                  // unique command positions in genom
    while (mutations.size() < mutatuionCount) // insert command position
    {
        mutations.insert(rand() % GENOM_SIZE);
    }
    // generate new commands on this positions
    for (auto i : mutations)
    {
        Bot::Command newCommand = genom[i];
        do
        {
            newCommand = GenerateCommand();
        } while (newCommand == genom[i]);
        genom[i] = newCommand;
    }
}

void Bot::reset()
{
    health = MAX_HEALTH;
    curCommand = 0;
    direction = (Bot::Direction)(std::rand() % DIRECTION_COUNT);
}