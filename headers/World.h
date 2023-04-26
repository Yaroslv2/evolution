#ifndef World_h
#define World_h

#include <vector>
#include <queue>
#include "Bot.h"
#include "Eat.h"
#include "Empty.h"
#include "Poison.h"
#include "Wall.h"
#include "Graphics.h"
#include <set>
#include <deque>

#define MAX_ACTION 10

class World
{
public:
    World();
    World(int, int);
    void Reset();
    void MakeTurn();
    bool needEvolve();
    void Evolve();
    const std::vector<std::vector<Object *>> &getPole();
    int score;

private:
    int n;
    int m;
    std::vector<std::vector<Object *>> pole;
    std::queue<std::pair<int, int>> botsCoord;
    std::pair<int, int> ChangeBotCoords(std::pair<int, int>, std::pair<int, int>, Bot *&);
    bool IsInPole(std::pair<int, int>);
    template <class T>
    void FillObject(int);
    std::pair<int, int> ProcessDirection(std::pair<int, int>, Bot *&);
    void reloadBotCoords();
    void insertObject(Object *);
    std::deque<Bot *> cemetery;
    void deleteFromCemetery(int);
};

#endif