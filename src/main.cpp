#include <thread>
#include <string>

#include "Board.hpp"
#include "Constants.hpp"

int main(int argc, char *args[])
{
    Board board("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    while (board.getIsPlaying())
    {
        if (board.getShouldUpdate())
        {
            board.update();
        }

        board.handleInput();
        board.render();
    }

    return 0;
}
