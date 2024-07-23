#include "Board.hpp"

void initializeCells(Cell (*cells)[CELLS][CELLS])
{
    for (int x = 0; x < CELLS; x++)
    {
        for (int y = 0; y < CELLS; y++)
        {
            (*cells)[x][y].setPosition(x, y);
        }
    }
}

Board::Board(const char *title, int xpos, int ypos)
{
    isPlaying = false;
    shouldUpdate = false;

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(title, xpos, ypos, (CELLS * CELL_SIZE), (CELLS * CELL_SIZE), window_flags);
    if (window == nullptr)
    {
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("Could not create renderer! SDL_Error: " + std::string(SDL_GetError()));
    }

    initializeCells(&cells);

    isPlaying = true;
}

void Board::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int x = 0; x < CELLS; x++)
    {
        for (int y = 0; y < CELLS; y++)
        {
            cells[x][y].render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}

void Board::update()
{
    SDL_Delay(100);

    bool nextState[CELLS][CELLS];

    for (int x = 0; x < CELLS; x++)
    {
        for (int y = 0; y < CELLS; y++)
        {
            int aliveNeighbors = 0;

            // check neighbours
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    // Skip the current cell itself
                    if (dx == 0 && dy == 0)
                        continue;

                    int nx = x + dx;
                    int ny = y + dy;

                    // Check if neighbour is within bounds and is alive
                    if (nx >= 0 && nx < CELLS && ny >= 0 && ny < CELLS)
                    {
                        if (cells[nx][ny].getIsAlive())
                        {
                            aliveNeighbors++;
                        }
                    }
                }
            }

            // Apply rules
            if (cells[x][y].getIsAlive())
            {
                // Dies if live neighbours < 2 or > 3
                nextState[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3);
            }
            else
            {
                // Becomes alive neighbours = 3
                nextState[x][y] = (aliveNeighbors == 3);
            }
        }
    }

    // Apply new state
    for (int x = 0; x < CELLS; x++)
    {
        for (int y = 0; y < CELLS; y++)
        {
            cells[x][y].setIsAlive(nextState[x][y]);
        }
    }
}

Cell *Board::getClickedCell()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    for (int x = 0; x < CELLS; ++x)
    {
        for (int y = 0; y < CELLS; ++y)
        {
            if (mouseX >= x * CELL_SIZE && mouseX < (x + 1) * CELL_SIZE &&
                mouseY >= y * CELL_SIZE && mouseY < (y + 1) * CELL_SIZE)
            {
                return &cells[x][y];
            }
        }
    }
    return nullptr;
}

void Board::handleInput()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type)
    {
    case SDL_QUIT:
    {
        isPlaying = false;
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
    {
        if (Cell *clickedCell = getClickedCell())
            clickedCell->handleClick(e.button.button);
    }
    break;
    case SDL_MOUSEMOTION:
    {
        if (Cell *clickedCell = getClickedCell())
            clickedCell->handleClick(e.button.button);
    }
    break;
    case SDL_KEYDOWN:
        // Determine key pressed
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            shouldUpdate = !shouldUpdate;
            break;
        case SDLK_BACKSPACE:
            break;
        case SDLK_w:
            break;
        case SDLK_q:
            break;
        default:
            break;
        }
    default:
        break;
    }
}
