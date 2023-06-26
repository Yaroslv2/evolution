#ifndef World_h
#define World_h

#include <vector>
#include <queue>
#include "Bot.h"
#include "Eat.h"
#include "Empty.h"
#include "Poison.h"
#include "Wall.h"
#include <set>
#include <deque>

#define MAX_ACTION 10

class World
{
public:
    World();
    void reset();
    void makeTurn();
    bool needEvolve();
    void evolve();
    const std::vector<std::vector<Object *>> &getPole();
    int score;

private:
    int n;
    int m;
    int eatOnMapCount;
    int poisonOnMapCount;
    std::vector<std::vector<Object *>> pole;
    std::queue<std::pair<int, int>> botsCoord;
    std::queue<std::pair<int, int>> feedCoord;
    std::queue<std::pair<int, int>> poisonCoord;
    std::pair<int, int> changeBotCoords(std::pair<int, int>, std::pair<int, int>, Bot *&);
    bool isInPole(std::pair<int, int>);
    template <class T>
    void fillObject(int);
    std::pair<int, int> processDirection(std::pair<int, int>, int);
    void reloadBotCoords();
    void insertObject(Object *);
    std::deque<Bot *> cemetery;
    void deleteFromCemetery(int);
    void feadRegenerate();
    void poisonRegenerate();
};

#endif