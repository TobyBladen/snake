// A file to implement Board class methods

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>

// Custom class header file imports
#include "Board.h"
#include "GameState.h"
#include "Rect.h"
#include "Renderer.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_BOARD)
#include <iostream>
#define BOARD_LOG(a) std::cout << "Board log: " << a << std::endl
#else
#define BOARD_LOG(a)
#endif

// Public method definitions

// Create a new board with viewport of specified location, width, and height
Board::Board(std::shared_ptr<Renderer> rnd, SDL_Rect pos) :
UIElement(rnd, pos)
{
    BOARD_LOG("Board created");
}

Board::~Board(void)
{
    BOARD_LOG("Board destroyed");
}

// Private method definitions

// Render all board content to the screen
void Board::render(void)
{
    BOARD_LOG("Could not render - required game state argument is missing");
}

// Render all board content to the screen
void Board::render(GameState& gs)
{
    std::shared_ptr<Renderer> lRend = rend.lock();
    if(lRend == nullptr)
    {
        BOARD_LOG("Could not render - Renderer was already destroyed");
    }
    else
    {
        SDL_RenderSetViewport(lRend->getRaw(), &pos);
        const int gridSize = gs.getGridSize();
        const int entityWidth = pos.w/(gridSize + 2);
        const int entityHeight = pos.h/(gridSize + 2);
        drawWalls(lRend, entityWidth, entityHeight);
        drawSnake(lRend, gs, entityWidth, entityHeight);
        drawFood(lRend, gs, entityWidth, entityHeight);
    }
}

// Render board outside walls to the screen
// with each square of specified width and height
void Board::drawWalls(std::shared_ptr<Renderer> rnd, const int entityWidth,
                      const int entityHeight)
{
    Rect wall(rnd, {0, 0, pos.w, entityHeight}, WALL_COLOR);
    wall.show();
    wall = Rect(rnd, { pos.w - entityWidth,
                       entityHeight,
                       entityWidth,
                       pos.h - (entityHeight * 2) },
                WALL_COLOR);
    wall.show();
    wall = Rect(rnd, { 0,
                       pos.h - entityHeight,
                       pos.w,
                       entityHeight },
                WALL_COLOR);
    wall.show();
    wall = Rect(rnd, { 0,
                       entityHeight,
                       entityWidth,
                       pos.h - (entityHeight * 2) },
                WALL_COLOR);
    wall.show();
}

// Render snake to the screen
// with each square of specified width and height
void Board::drawSnake(std::shared_ptr<Renderer> rnd, GameState& gs,
                      const int entityWidth, const int entityHeight)
{
    int snakeLength = gs.getSnakeLength();
    for(int i = 0; i < snakeLength; i++)
    {
        Point p = gs.getSnakePntAt(i);
        int x = (p.getX() + 1) * entityWidth;
        int y = (p.getY() + 1) * entityHeight;
        Rect r(rnd, { x, y, entityWidth, entityHeight }, SNAKE_COLOR);
        r.show();
    }
}

// Render food to the screen
// with square of specified width and height
void Board::drawFood(std::shared_ptr<Renderer> rnd, GameState& gs,
                     const int entityWidth, const int entityHeight)
{
    Point foodLoc = gs.getFood();
    int x = (foodLoc.getX() + 1) * entityWidth;
    int y = (foodLoc.getY() + 1) * entityHeight;
    Rect r(rnd, { x, y, entityWidth, entityHeight}, FOOD_COLOR);
    r.show();
}
