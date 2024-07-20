#include "EventHandler.h"

void EventHandler::handleEvents(GOL *gol, bool *play)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type)
    {
    case SDL_QUIT:
        *play = false;
        break;
        // Left/right mouse button down
    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT)
            handleClick(gol, SDL_BUTTON_LEFT);
        else
            handleClick(gol, SDL_BUTTON_RIGHT);
        break;
        // Left/right mouse button up
    case SDL_MOUSEBUTTONUP:
        leftMouseDown = false;  // Disable mouse drag
        rightMouseDown = false; // Disable mouse drag
        break;
    case SDL_MOUSEMOTION:
        if (leftMouseDown)
            handleClick(gol, SDL_BUTTON_LEFT); // Allow mouse drag draw
        if (rightMouseDown)
            handleClick(gol, SDL_BUTTON_RIGHT); // Allow mouse drag draw
        break;
        // Keyboard event
    case SDL_KEYDOWN:
        // Determine key pressed
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            gol->isStarted = !gol->isStarted; // Toggle game
            if (gol->isStarted)
                std::cout << "-- Game started" << std::endl;
            else
                std::cout << "-- Game stopped" << std::endl;
            break;
        case SDLK_BACKSPACE:
            gol->clearGrid(); // Clear grid
            std::cout << "-- Grid cleared" << std::endl;
            break;
        case SDLK_w:
            gol->createShape(GOL::ShapeType::MIDDLE_LINE);
            break;
        case SDLK_q:
            gol->createShape(GOL::ShapeType::PERIMETER_BOX);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void EventHandler::handleClick(GOL *gol, int key)
{
    if (key == SDL_BUTTON_LEFT)
        leftMouseDown = true;
    else
        rightMouseDown = true;

    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse); // Get current mouse coordinates

    // Calculate the number of columns and rows
    int numCols = gol->gridWidth / gol->cellSize;
    int numRows = gol->gridHeight / gol->cellSize;

    // Repeat for the number of rows and columns
    for (int x = 0; x < numCols; x++)
    {
        for (int y = 0; y < numRows; y++)
        {
            // Calculate the index in the 1D array
            int index = x * numRows + y;

            // Calculate the boundaries of the current cell
            int cellXMin = x * gol->cellSize;
            int cellXMax = cellXMin + gol->cellSize;
            int cellYMin = y * gol->cellSize;
            int cellYMax = cellYMin + gol->cellSize;

            // Check if the mouse click is within the cell's boundaries
            if (xMouse >= cellXMin && xMouse < cellXMax)
            {
                if (yMouse >= cellYMin && yMouse < cellYMax)
                {
                    if (key == SDL_BUTTON_LEFT)
                        gol->grid[index].active = true;
                    else
                        gol->grid[index].active = false;
                }
            }
        }
    }
}
