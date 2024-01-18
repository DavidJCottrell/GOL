#include "EventHandler.h"

void EventHandler::handleEvents(GOL* gol, bool* play) {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type) {
    case SDL_QUIT:
        *play = false;
        break;
        // Left/right mouse button down
    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT) handleClick(gol, SDL_BUTTON_LEFT);
        else handleClick(gol, SDL_BUTTON_RIGHT);
        break;
        // Left/right mouse button up
    case SDL_MOUSEBUTTONUP:
        leftMouseDown = false; //Disable mouse drag
        rightMouseDown = false; //Disable mouse drag
        break;
    case SDL_MOUSEMOTION:
        if (leftMouseDown) handleClick(gol, SDL_BUTTON_LEFT); //Allow mouse drag draw
        if (rightMouseDown) handleClick(gol, SDL_BUTTON_RIGHT); //Allow mouse drag draw
        break;
        // Keyboard event
    case SDL_KEYDOWN:
        // Determine key pressed
        switch (e.key.keysym.sym) {
        case SDLK_SPACE:
            gol->isStarted = !gol->isStarted; //Toggle game
            if (gol->isStarted) std::cout << "-- Game started" << std::endl;
            else std::cout << "-- Game stopped" << std::endl;
            break;
        case SDLK_BACKSPACE:
            gol->clearGrid(); //Clear grid
            std::cout << "-- Grid cleared" << std::endl;
            break;
        case SDLK_q:
            gol->premade(gol->PremadeShape::Perimiter);
            break;
        case SDLK_w:
            gol->premade(gol->PremadeShape::VerticalLineMiddle);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void EventHandler::handleClick(GOL* gol, int key) {
    if (gol->isStarted) return;

    if (key == SDL_BUTTON_LEFT) leftMouseDown = true;
    else rightMouseDown = true;

    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse); //Get current mouse coordinates

    //repeat for number of rows and columns
    for (int x = 0; x < gol->grid_width / gol->grid_gap; x++) {
        for (int y = 0; y < gol->grid_height / gol->grid_gap; y++) {
            //Check if clicked within limits of cell            
            if (xMouse < gol->grid[x][y].limit_x && xMouse > gol->grid[x][y].limit_x - gol->grid_gap) {
                if (yMouse < gol->grid[x][y].limit_y && yMouse > gol->grid[x][y].limit_y - gol->grid_gap) {
                    if (key == SDL_BUTTON_LEFT) gol->grid[x][y].active = true;
                    else gol->grid[x][y].active = false;
                }
            }
        }
    }
}