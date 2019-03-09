// A file to implement GameState class methods

// Standard header file imports
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>

// Custom class header file imports
#include "GameState.h"
#include "Point.h"
#include "Snake.h"

// Define macro debug log functionality
#include "log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_GAMESTATE)
#include <iostream>
#define GAMESTATE_LOG(a) std::cout << "GameState log: " << a << std::endl
#else
#define GAMESTATE_LOG(a)
#endif

// Public method definitions

// Set up new game with specified grid size and snake length.
// Place an item of food at random coordinates
GameState::GameState(const int gridSize0, const int snakeStLen0, int hiscore0) :
difficulty(UNDEFINED),
food(),
gridSize(gridSize0),
hiscore(hiscore0),
paused(false),
play(true),
snake(nullptr),
snakeStLen(snakeStLen0)
{
    try
    {
        checkArgs(gridSize0, snakeStLen0);
        srand((unsigned int)time(nullptr));
        food = randomPoint();
        snake = std::make_unique<Snake>(snakeStLen);
        GAMESTATE_LOG("Game State created");
    }
    catch(std::invalid_argument& e)
    {
        GAMESTATE_LOG("Initalization error - invalid argument");
        throw std::invalid_argument(e.what());
    }
}

GameState::~GameState(void)
{
    GAMESTATE_LOG("Game State destroyed");
}

bool GameState::gamePaused(void)
{
    return paused;
}

enum difficulty GameState::getDifficulty(void)
{
    return difficulty;
}

Point GameState::getFood(void)
{
    return food;
}

int GameState::getGridSize()
{
    return gridSize;
}

// Get the highscore up to this point
int GameState::getHiscore(void)
{
    return hiscore;
}

// Get the number of pieces of food eaten so far
int GameState::getScore(void)
{
    return snake->length() - snakeStLen;
}

enum direction GameState::getSnakeDir(void)
{
    return snake->getDir();
}

int GameState::getSnakeLength(void)
{
    return snake->length();
}

// Get the location of snake point at index 'i'
Point GameState::getSnakePntAt(int i)
{
    try
    {
        return snake->pntAt(i);
    }
    catch(std::out_of_range& e)
    {
        GAMESTATE_LOG(std::string("Out of snake's range: ") + e.what());
        throw std::out_of_range(std::to_string(i));
    }
}

// Return the starting length for a new snake
int GameState::getSnakeStLen(void)
{
    return snakeStLen;
}

// Move snake forward one square
void GameState::moveSnake(void)
{
    Point nextHead = snake->getNext();
    if(foodCollision(nextHead))
    {
        snake->grow();
        food = randomPoint();
        int score = getScore();
        if(score > hiscore) {
            hiscore = score;
        }
    }
    else if(wallCollision(nextHead) || bodyCollision(nextHead))
    {
        snake->kill();
    }
    else
    {
        snake->move();
    }
}

void GameState::pause(void)
{
    paused = true;
}

bool GameState::playing()
{
    return play;
}

void GameState::quit()
{
    play = false;
}

// Reinstantiate snake and food ready for a new game
void GameState::reset(void)
{
    snake = std::make_unique<Snake>(snakeStLen);
    play = true;
    paused = false;
    food = randomPoint();
    difficulty = UNDEFINED;
    GAMESTATE_LOG("Game State reset");
}

void GameState::resume(void)
{
    paused = false;
}

void GameState::setDifficulty(enum difficulty difficulty0)
{
    difficulty = difficulty0;
}

void GameState::setFood(Point food0)
{
    GAMESTATE_LOG("Warning - food location was manually overridden");
    food = food0;
}

void GameState::setSnakeDir(enum direction dir0)
{
    snake->setDir(dir0);
}

bool GameState::snakeAlive()
{
    return snake->alive();
}

// Private method definitions

// Return boolean to indicate if snake has collided with itself or not
bool GameState::bodyCollision(Point head)
{
    for(int i = 0; i < snake->length() - 2; i++)
    {
        Point p = snake->pntAt(i);
        if(p.same(head))
        {
            return true;
        }
    }
    return false;
}

// Validate object constructor arguments
void GameState::checkArgs(const int gridSize, const int snakeStLen)
{
    std::string err = "";
    if(gridSize <= 0)
    {
        err = "Invalid grid size: " + std::to_string(gridSize);
    }
    else if(snakeStLen <=0)
    {
        err = "Invalid snake length: " + std::to_string(snakeStLen);
    }
    else if(gridSize < snakeStLen)
    {
        err = "Grid size '" + std::to_string(gridSize) +
              "' is smaller than snake length '" +
              std::to_string(snakeStLen) + "'";
    }
    if(err != "")
    {
        throw std::invalid_argument(err);
    }
}

// Return boolean to indicate if snake has collided with food or not
bool GameState::foodCollision(Point head)
{
    if(food.same(head))
    {
        return true;
    }
    return false;
}

// Generate a random 2D (x,y) coordinate on the grid
Point GameState::randomPoint(void)
{
    return Point(rand() % gridSize, rand() % gridSize);
}

// Return boolean to indicate if snake has collided with wall or not
bool GameState::wallCollision(Point head)
{
    int headX = head.getX();
    int headY = head.getY();
    if(headX < 0 ||
       headY < 0 ||
       headX >= gridSize ||
       headY >= gridSize)
    {
        return true;
    }
    return false;
}
