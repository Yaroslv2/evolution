#include "headers/Graphics.h"
#include "headers/World.h"
#include <iostream>

int main()
{
    srand(time(NULL));
    int n = 40, m = 20, rect_size = 20, outline_tricknes_size = 2;
    World world(n, m);
    Graphics graphics;
    int era = 1;
    // while (true)
    // {
    //     std::vector<std::vector<Object *>> v = world.getPole();
    //     for (int i = 0; i < m; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             if (v[j][i]->GetType() == Object::Type::BOT)
    //             {
    //                 std::cout << "1 ";
    //             }
    //             else
    //                 std::cout << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    //     world.MakeTurn();
    //     getchar();
    // }
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
            default:
                break;
            }
        }
        if (world.needEvolve())
        {
            era++;
            std::cout << era << " " << world.score << std::endl;
            world.Evolve();
        }
        world.MakeTurn();
        graphics.Draw(world.getPole());
    }

    return 0;
}