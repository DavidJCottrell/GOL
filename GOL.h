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
    GOL(int width, int height, int gap, int game_speed);
	~GOL();

    struct cell {
        int limit_x;
        int limit_y;
        int x; // X position in grid
        int y; // Y position in grid
        bool active;
    };


    void clearGrid();
    void premade(int shape) const; //Draw premade configurations

    int grid_width;
    int grid_height;
    int grid_gap;
    unsigned int gameSpeed;
    bool isStarted = false;

    cell* grid{};

    void tick();

private:
    static const int defaultGridWidth = 640;
    static const int defaultGridHeight = 480;
    static const int defaultGridGap = 10;
    static const unsigned int defaultGameSpeed = 100;
    void initializeGrid();
};

