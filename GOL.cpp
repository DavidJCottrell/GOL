#include "GOL.h"

GOL::GOL() {

    //Fill grid array with square structs
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {
            grid[x][y] = { (x + 1) * grid_gap, (y + 1) * grid_gap, x, y, false };
        }
    }

    std::cout << "\n--------------------------- " << std::endl;
    std::cout << "- Create cells by left clicking or holding left click and dragging. (Game must be stopped first)" << std::endl;
    std::cout << "- Delete cells by the same way but right clicking." << std::endl;
    std::cout << "- Clear grid by pressing backspace." << std::endl;
    std::cout << "- Press space to start/stop...\n" << std::endl;
}

GOL::~GOL() {
    std::cout << "\n\n-- Exiting." << std::endl;
    std::cout << "\n--------------------------- " << std::endl;
}

void GOL::premade(int shape) {
    if (shape == 1) {
        for (int x = 0; x < grid_width / grid_gap; x++)
            for (int y = 0; y < grid_height / grid_gap; y++)
                if (x == 0 || y == 0 || x == grid_width / grid_gap - 1 || y == grid_height / grid_gap - 1)
                    grid[x][y].active = true;
    }
    else if (shape == 2) {
        for (int x = 0; x < grid_width / grid_gap; x++)
            for (int y = 0; y < grid_height / grid_gap; y++)
                if (x == (grid_width / grid_gap - 1) / 2)
                    grid[x][y].active = true;
    }
}

// Sets all cell's active property to false
void GOL::clearGrid() {
    for (int x = 0; x < grid_width / grid_gap; x++)
        for (int y = 0; y < grid_height / grid_gap; y++)
            grid[x][y].active = false;
}

//Apply rules to each cell
void GOL::tick() {

    // *** RULES NEED TO BE APPLIED SIMULTANEOUSLY SO CHANGES ARE MADE TO THE COPY, THEN COPIED BACK TO THE ORIGINAL ***

    cell grid_copy[grid_width / grid_gap][grid_height / grid_gap];
    //Create copy of current grid
    for (int x = 0; x < grid_width / grid_gap; x++)
        for (int y = 0; y < grid_height / grid_gap; y++)
            grid_copy[x][y] = grid[x][y];

    int aliveNeighbors = 0;
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {

            //Check if top cell exists
            if (y > 0 && grid[x][y - 1].active) aliveNeighbors++; // Check if top is alive
            //Check if top right cell exists
            if ((x < grid_width / grid_gap - 1 || y > 0) && grid[x + 1][y - 1].active) aliveNeighbors++; // Check if top right cell is alive
            //Check if right cell exists
            if ((x < grid_width / grid_gap - 1) && grid[x + 1][y].active) aliveNeighbors++; // Check if right is alive
            //Check if bottom right cell exists
            if ((y < grid_height / grid_gap - 1 || x < grid_width / grid_gap - 1) && grid[x + 1][y + 1].active) aliveNeighbors++; // Check if bottom right is alive
            //Check if bottom cell exists
            if ((y < grid_height / grid_gap - 1) && grid[x][y + 1].active) aliveNeighbors++; // Check if bottom is alive
            //Check if bottom left cell exists
            if ((x > 0 || y < grid_height / grid_gap - 1) && grid[x - 1][y + 1].active) aliveNeighbors++; // Check if bottom left is alive
            //Check if left cell exists
            if (x > 0 && grid[x - 1][y].active) aliveNeighbors++; // Check if left is alive
            //Check if top left cell exists
            if ((x > 0 || y > 0) && grid[x - 1][y - 1].active) aliveNeighbors++; // Check if top left is alive

            //Current cell is alive
            if (grid[x][y].active) {
                //Less than or 2 or more than 3 die
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    grid_copy[x][y].active = false;
                }
            }
            //Current cell is not alive and has exactly 3 neighbors
            else if (aliveNeighbors == 3) {
                grid_copy[x][y].active = true;
            }
            aliveNeighbors = 0; //Reset neighbor count
        }
    }

    //Put contents into original array
    for (int x = 0; x < grid_width / grid_gap; x++)
        for (int y = 0; y < grid_height / grid_gap; y++)
            grid[x][y] = grid_copy[x][y];
}
