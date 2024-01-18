#include "Renderer.h"

void Renderer::DrawGrid(GOL* gol) {

    SDL_SetRenderDrawColor(renderer, 35, 35, 35, SDL_ALPHA_OPAQUE);

    //Draw vertical lines
    for (int x = 1; x * gol->grid_gap <= gol->grid_width; x++) {
        SDL_RenderDrawLine(renderer,
            x * gol->grid_gap, 0,
            x * gol->grid_gap, gol->grid_height
        );
    }
    //Draw horizontal lines
    for (int y = 1; y * gol->grid_gap <= gol->grid_height; y++) {
        SDL_RenderDrawLine(renderer,
            0, y * gol->grid_gap,
            gol->grid_width, y * gol->grid_gap
        );
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    //Update for clicked alive cells
    for (int x = 0; x < GOL::grid_width / GOL::grid_gap; x++) {
        for (int y = 0; y < GOL::grid_height / GOL::grid_gap; y++) {
            if (gol->grid[x][y].active) {
                SDL_Rect rect = {
                    gol->grid[x][y].limit_x - GOL::grid_gap, //location x
                    gol->grid[x][y].limit_y - GOL::grid_gap, //location y
                    GOL::grid_gap, GOL::grid_gap //h, w
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::render(GOL* gol) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    DrawGrid(gol);
    if (gol->isStarted) {
        gol->tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(GOL::gameSpeed));
    }
}

Renderer::Renderer(const char* title, int xpos, int ypos, int width, int height) {

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        // Exit if error
    }

    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        // Exit if error
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Could not create renderer! SDL_Error: %s\n", SDL_GetError());
        // Exit if error
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
