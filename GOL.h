#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>
#include <thread>

class GOL
{
public:
	GOL();
	~GOL();

    struct cell {
        int limit_x;
        int limit_y;
        int x; // X position in grid
        int y; // Y position in grid
        bool active;
    };

    void tick();
    void clearGrid();
    void premade(int shape); //Draw premade configurations

    static const int grid_width = 640;
    static const int grid_height = 480;
    static const int grid_gap = 10;
    static const unsigned int gameSpeed = 100;
    bool isStarted = false;

    cell grid[grid_width / grid_gap][grid_height / grid_gap];
};

