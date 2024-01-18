#include "Renderer.h"
#include "GOL.h"
#include "EventHandler.h"
#include <thread>
#include <string>


int main(int argc, char* args[]) {
    bool play = true;
    GOL* gol = new GOL();
    EventHandler eventHandler;
    Renderer renderer(
        "Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GOL::grid_width,
        GOL::grid_height
    );

    std::thread eventHandlerThread([&]() {
        while (play) {
            renderer.render(gol);
        }
    });

    while (play) {
        eventHandler.handleEvents(gol, &play);
    }

    eventHandlerThread.join();

    delete gol;

    return 0;
}
