#pragma once

#include <SDL.h>
#include <iostream>
#include <chrono>
#include <thread>

class GOL
{
public:
    GOL();
    GOL(int width, int height, int gap, int game_speed);
    ~GOL();

    struct cell
    {
        int x; // X position in grid
        int y; // Y position in grid
        bool active;
    };

    enum ShapeType
    {
        PERIMETER_BOX,
        MIDDLE_LINE
    };

    void clearGrid() const;
    void createShape(ShapeType shape) const; // Draw premade configurations

    int gridWidth;
    int gridHeight;
    int cellSize;
    unsigned int gameSpeed;
    bool isStarted = false;

    cell *grid{};

    void tick() const;

private:
    static const int defaultGridWidth = 640;
    static const int defaultGridHeight = 480;
    static const int defaultCellSize = 10;
    static const unsigned int defaultGameSpeed = 100;
    void initializeGrid();
};
