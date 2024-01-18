#include "GOL.h"

GOL::GOL(int width, int height, int gap, int game_speed)
        : grid_width(width), grid_height(height),
          grid_gap(gap), gameSpeed(game_speed)
{
    initializeGrid();
}

GOL::GOL()
        : grid_width(defaultGridWidth), grid_height(defaultGridHeight),
          grid_gap(defaultGridGap), gameSpeed(defaultGameSpeed)
{
    initializeGrid();
}

void GOL::initializeGrid()
{
    grid = new cell[grid_width / grid_gap * grid_height / grid_gap];

    // Fill grid array with square structs
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {
            int index = x * (grid_height / grid_gap) + y;
            grid[index] = { (x + 1) * grid_gap, (y + 1) * grid_gap, x, y, false };
        }
    }
}

GOL::~GOL()
{
    delete[] grid;

    std::cout << "\n\n-- Exiting." << std::endl;
    std::cout << "\n--------------------------- " << std::endl;
}

void GOL::premade(int shape) const {
    if (shape == 1) {
        for (int x = 0; x < grid_width / grid_gap; x++)
            for (int y = 0; y < grid_height / grid_gap; y++)
                if (x == 0 || y == 0 || x == grid_width / grid_gap - 1 || y == grid_height / grid_gap - 1)
                    grid[x * (grid_height / grid_gap) + y].active = true;
    }
    else if (shape == 2) {
        for (int x = 0; x < grid_width / grid_gap; x++)
            for (int y = 0; y < grid_height / grid_gap; y++)
                if (x == (grid_width / grid_gap - 1) / 2)
                    grid[x * (grid_height / grid_gap) + y].active = true;
    }
}

// Sets all cell's active property to false
void GOL::clearGrid() {
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {
            // Calculate the index in the 1D array
            int index = x * (grid_height / grid_gap) + y;
            grid[index].active = false;
        }
    }
}

//Apply rules to each cell
void GOL::tick() {
    // Create a dynamic array for the copy of the grid
    cell* grid_copy = new cell[grid_width / grid_gap * grid_height / grid_gap];

    // Create copy of the current grid
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {
            int index = x * (grid_height / grid_gap) + y;
            grid_copy[index] = grid[index];
        }
    }

    int aliveNeighbors = 0;
    for (int x = 0; x < grid_width / grid_gap; x++) {
        for (int y = 0; y < grid_height / grid_gap; y++) {

            // Check if top cell exists
            if (y > 0 && grid[x * (grid_height / grid_gap) + (y - 1)].active) aliveNeighbors++; // Check if top is alive
            // Check if top right cell exists
            if ((x < grid_width / grid_gap - 1 || y > 0) && grid[(x + 1) * (grid_height / grid_gap) + (y - 1)].active) aliveNeighbors++; // Check if top right cell is alive
            // Check if right cell exists
            if ((x < grid_width / grid_gap - 1) && grid[(x + 1) * (grid_height / grid_gap) + y].active) aliveNeighbors++; // Check if right is alive
            // Check if bottom right cell exists
            if ((y < grid_height / grid_gap - 1 || x < grid_width / grid_gap - 1) && grid[(x + 1) * (grid_height / grid_gap) + (y + 1)].active) aliveNeighbors++; // Check if bottom right is alive
            // Check if bottom cell exists
            if ((y < grid_height / grid_gap - 1) && grid[x * (grid_height / grid_gap) + (y + 1)].active) aliveNeighbors++; // Check if bottom is alive
            // Check if bottom left cell exists
            if ((x > 0 || y < grid_height / grid_gap - 1) && grid[(x - 1) * (grid_height / grid_gap) + (y + 1)].active) aliveNeighbors++; // Check if bottom left is alive
            // Check if left cell exists
            if (x > 0 && grid[(x - 1) * (grid_height / grid_gap) + y].active) aliveNeighbors++; // Check if left is alive
            // Check if top left cell exists
            if ((x > 0 || y > 0) && grid[(x - 1) * (grid_height / grid_gap) + (y - 1)].active) aliveNeighbors++; // Check if top left is alive

            // Current cell is alive
            if (grid[x * (grid_height / grid_gap) + y].active) {
                // Less than 2 or more than 3 die
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    grid_copy[x * (grid_height / grid_gap) + y].active = false;
                }
            }
                // Current cell is not alive and has exactly 3 neighbors
            else if (aliveNeighbors == 3) {
                grid_copy[x * (grid_height / grid_gap) + y].active = true;
            }
            aliveNeighbors = 0; // Reset neighbor count
        }
    }

    // Copy contents back to the original array
    for (int i = 0; i < grid_width / grid_gap * grid_height / grid_gap; i++) {
        grid[i] = grid_copy[i];
    }

    // Deallocate memory for the copy of the grid
    delete[] grid_copy;
}

