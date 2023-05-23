#include "headers/Graphics.h"
#include "headers/World.h"

#define SPEED_TIME_DELTA 7

int main()
{
    srand(time(NULL));
    int n = 40, m = 20, speed = 7; // sizes of map
    bool pause = false, needDraw = true;
    World world(n, m); // create world with map n x m
    Graphics graphics; // create graphics
    int era = 1;       // generation count
    while (graphics.IsWindowOpen())
    {
        // processing events
        for (int i = 0; i < speed; i++)
        {
            std::vector<Graphics::Event> events = graphics.GetWindowEvents(); // get events from window
            for (auto i : events)
            {
                switch (i)
                {
                case Graphics::Event::CLOSE: // close event
                    return 0;
                    break;
                case Graphics::Event::PAUSE: // on/off pause of algorithm
                    pause = !pause;
                    break;
                case Graphics::Event::DECREASE_SPEED:
                    speed /= SPEED_TIME_DELTA;
                    if (speed == 0)
                        speed = 1;
                    break;
                case Graphics::Event::INCREASE_SPEED:
                    speed *= SPEED_TIME_DELTA;
                    break;
                case Graphics::Event::SWITCH_DRAW:
                    needDraw = !needDraw;
                    break;
                default:
                    break;
                }
            }
        }
        if (world.needEvolve()) // check is it necessary to create a new generation
        {
            graphics.getNewScore(era++, world.score); // save generation`s score
            world.evolve();                           // create new generation
        }
        if (!pause) // pause algorithm or not
        {
            world.makeTurn(); // actions of bots
        }
        if (needDraw)
            graphics.Draw(world.getPole(), era); // draw new map
    }

    return 0;
}