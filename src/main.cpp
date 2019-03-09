// Standard header file imports
#include <iostream>
#include <stdexcept>

// Custom class header file imports
#include "Display.h"
#include "GameState.h"

// Import presets of game logic settings
#include "config.h"
// Import game text content
#include "content.h"
// Import stylesheet
#include "stylesheet.h"

int main(void)
{
    try
    {
        GameState gs(GRID_SIZE, SNAKE_LENGTH, ST_SCORE);
        Display d(MAIN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, BOARD_HEIGHT);
        do
        {
            d.pollEvents(gs);
            if(gs.snakeAlive() && !gs.gamePaused()) {
                gs.moveSnake();
            }
            d.show(gs);
            d.wait(FINTERVAL);
        }
        while(gs.playing());
        return 0;
    }
    catch(std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }
}
