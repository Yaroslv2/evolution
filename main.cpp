#include "headers/Graphics.h"
#include "headers/World.h"

int main()
{
    srand(time(NULL));
    int n = 40, m = 20; // sizes of map
    bool pause = false;
    World world(n, m); // create world with map n x m
    Graphics graphics; // create graphics
    int era = 1;       // generation count
    while (graphics.IsWindowOpen())
    {
        // processing events
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
            default:
                break;
            }
        }
        if (world.needEvolve()) // check is it necessary to create a new generation
        {
            graphics.getNewScore(era++, world.score); // save generation`s score
            world.Evolve();                           // create new generation
        }
        if (!pause) // pause algorithm or not
        {
            world.MakeTurn();                    // actions of bots
            graphics.Draw(world.getPole(), era); // draw new map
        }
    }

    return 0;
}