#ifndef CELL_H
#define CELL_H

#pragma once

#include <SDL.h>

#include "Constants.hpp"

class Cell
{
public:
    Cell() : isAlive(false), gridPosX(0), gridPosY(0){};

    void setPosition(int x, int y);
    void render(SDL_Renderer *renderer);

    void handleClick(Uint8 mouseButton);
    bool getIsAlive() const { return isAlive; }
    bool setIsAlive(bool alive) { return isAlive = alive; }

private:
    bool isAlive;

    int gridPosX;
    int gridPosY;
    SDL_Rect rect;
};

#endif