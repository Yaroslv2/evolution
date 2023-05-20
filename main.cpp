#include "headers/Graphics.h"
#include "headers/World.h"
#include <iostream>

int main()
{
    srand(time(NULL));
    int n = 40, m = 20, rect_size = 20, outline_tricknes_size = 2;
    bool pause = false;
    World world(n, m);
    Graphics graphics;
    int era = 1;
    while (graphics.IsWindowOpen())
    {
        std::vector<Graphics::Event> events = graphics.GetWindowEvents();
        for (auto i : events)
        {
            switch (i)
            {
            case Graphics::Event::CLOSE:
                return 0;
                break;
            case Graphics::Event::PAUSE:
                pause = !pause;
            default:
                break;
            }
        }
        if (world.needEvolve())
        {
            graphics.getNewScore(era++, world.score);
            world.Evolve();
        }
        if (!pause)
        {
            world.MakeTurn();
            graphics.Draw(world.getPole(), era);
        }
    }

    return 0;
}