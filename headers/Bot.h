#ifndef Bot_h
#define Bot_h

#include "Object.h"
#include <vector>
#include <cstdlib>
#include <time.h>

#define MAX_HEALTH 90
#define GENOM_SIZE 64
#define COMMAND_COUNT 6
#define DIRECTION_COUNT 8

class Bot : public Object
{
public:
    Bot();
    Bot(const Bot &);
    int GetHealth();
    enum class Action
    {
        VOID,
        GO,
        EAT,
        CONVERT,
        LOOK
    };
    enum class Direction
    {
        UP_LEFT,
        UP,
        UP_RIGHT,
        RIGHT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
        LEFT
    };
    void Feed(int);
    void Poison(int);
    Bot::Direction GetDirection();
    Bot::Action MakeAction(Object::Type);
    void evolve(int);
    void reset();

private:
    enum class Command
    {
        GO,
        TURN_LEFT,
        TURN_RIGHT,
        EAT,
        LOOK,
        CONVERT
    };
    std::vector<Bot::Command> genom;
    int health;
    Bot::Direction direction;
    int curCommand;
    Command GenerateCommand();
};

#endif