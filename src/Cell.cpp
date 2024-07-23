#include "Cell.hpp"

void Cell::setPosition(int x, int y)
{
    gridPosX = x;
    gridPosY = y;

    rect = {
        gridPosX * CELL_SIZE, // location x
        gridPosY * CELL_SIZE, // location y
        CELL_SIZE, CELL_SIZE  // w, h
    };
}

void Cell::render(SDL_Renderer *renderer)
{
    if (isAlive)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 35, 35, 35, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Cell::handleClick(Uint8 mouseButton)
{
    if (mouseButton == SDL_BUTTON_LEFT)
    {
        isAlive = true;
    }
    else if (mouseButton == SDL_BUTTON_RIGHT)
    {
        isAlive = false;
    }
}
