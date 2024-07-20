#include "Renderer.h"
#include "GOL.h"
#include "EventHandler.h"
#include <thread>
#include <string>

int main(int argc, char *args[])
{
    bool play = true;

    int const cellSize = 15;
    int const width = cellSize * 64;
    int const height = cellSize * 48;
    int const gameSpeed = 100; // 100ms delay between updates

    GOL *gol = new GOL(width, height, cellSize, gameSpeed);

    EventHandler eventHandler;
    Renderer renderer(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gol->gridWidth,
        gol->gridHeight);

    std::cout << "\n--------------------------- " << std::endl;
    std::cout << "- Create cells by left clicking or holding left click and dragging. (Game must be stopped first)" << std::endl;
    std::cout << "- Delete cells by the same way but right clicking." << std::endl;
    std::cout << "- Clear grid by pressing backspace." << std::endl;
    std::cout << "- Press space to start/stop...\n"
              << std::endl;

    while (play)
    {
        eventHandler.handleEvents(gol, &play);
        renderer.render(gol);
    }

    delete gol;

    return 0;
}
