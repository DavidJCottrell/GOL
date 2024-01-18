#include "Renderer.h"
#include "GOL.h"
#include "EventHandler.h"
#include <thread>
#include <string>


int main(int argc, char* args[]) {
    bool play = true;
    GOL* gol = new GOL(640, 480, 10, 100);
    EventHandler eventHandler;
    Renderer renderer(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gol->grid_width,
        gol->grid_height
    );

    std::thread eventHandlerThread([&]() {
        while (play) {
            renderer.render(gol);
        }
    });

    std::cout << "\n--------------------------- " << std::endl;
    std::cout << "- Create cells by left clicking or holding left click and dragging. (Game must be stopped first)" << std::endl;
    std::cout << "- Delete cells by the same way but right clicking." << std::endl;
    std::cout << "- Clear grid by pressing backspace." << std::endl;
    std::cout << "- Press space to start/stop...\n" << std::endl;

    while (play) {
        eventHandler.handleEvents(gol, &play);
    }

    eventHandlerThread.join();

    delete gol;

    return 0;
}
