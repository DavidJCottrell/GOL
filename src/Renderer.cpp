#include "Renderer.h"

void Renderer::DrawGrid(GOL *gol)
{
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, SDL_ALPHA_OPAQUE);

    // Draw vertical lines
    for (int x = 1; x * gol->cellSize <= gol->gridWidth; x++)
    {
        SDL_RenderDrawLine(renderer,
                           x * gol->cellSize, 0,
                           x * gol->cellSize, gol->gridHeight);
    }
    // Draw horizontal lines
    for (int y = 1; y * gol->cellSize <= gol->gridHeight; y++)
    {
        SDL_RenderDrawLine(renderer,
                           0, y * gol->cellSize,
                           gol->gridWidth, y * gol->cellSize);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    // Update for clicked alive cells
    int numCols = gol->gridWidth / gol->cellSize;
    int numRows = gol->gridHeight / gol->cellSize;

    for (int x = 0; x < numCols; x++)
    {
        for (int y = 0; y < numRows; y++)
        {
            // Calculate the index in the 1D array
            int index = x * numRows + y;

            if (gol->grid[index].active)
            {
                SDL_Rect rect = {
                    x * gol->cellSize,           // location x
                    y * gol->cellSize,           // location y
                    gol->cellSize, gol->cellSize // w, h
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::render(GOL *gol)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    DrawGrid(gol);
    if (gol->isStarted)
    {
        gol->tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(gol->gameSpeed));
    }
}

Renderer::Renderer(const char *title, int xpos, int ypos, int width, int height)
{

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags);
    if (window == nullptr)
    {
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Could not create renderer! SDL_Error: " + std::string(SDL_GetError()));
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
