#ifndef BOARD_H
#define BOARD_H

#pragma once

#include "SDL.h"
#include <stdexcept>
#include <string>
#include <iostream>

#include "Constants.hpp"
#include "Cell.hpp"

class Board
{
public:
    Board(const char *title, int xpos, int ypos);

    Cell cells[CELLS][CELLS];

    void render();
    void update();
    void handleInput();

    bool getIsPlaying() const
    {
        return isPlaying;
    }

    bool getShouldUpdate() const
    {
        return shouldUpdate;
    }

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isPlaying;
    bool shouldUpdate;

    Cell *getClickedCell();
};

#endif