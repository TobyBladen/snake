// A file to implement Snake class methods

// Standard header file imports
#include <stdexcept>
#include <string>
#include <vector>

// Custom class header file imports
#include "Point.h"
#include "Snake.h"

// Import presets of game logic settings
#include "config.h"

// Define macro debug log functionality
#include "log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_SNAKE)
#include <iostream>
#define SNAKE_LOG(a) std::cout << "Snake log: " << a << std::endl
#else
#define SNAKE_LOG(a)
#endif

// Public method definitions

// Mark snake as alive and heading East.
// Initialise a vector of points of size 'len' to represent snake position.
Snake::Snake(const int len) :
dir(EAST),
living(true)
{
    if(len <= 0) throw std::invalid_argument(std::to_string(len));
    else
    {
        for(int i = 0; i < len; i++)
        {
            body.push_back(Point(STARTING_WALL_GAP + i, STARTING_WALL_GAP));
        }
        calculateNext();
        SNAKE_LOG("Snake created");
    }
}

// Free all points in vector representing snake position
Snake::~Snake(void)
{
    SNAKE_LOG("Snake destroyed");
}

bool Snake::alive(void)
{
    return living;
}

enum direction Snake::getDir(void)
{
    return dir;
}

Point Snake::getNext(void)
{
    return next;
}

// Increase the snake length by one by adding a new head
void Snake::grow(void)
{
    body.push_back(next);
    calculateNext();
}

// Mark snake as no longer alive
void Snake::kill(void)
{
    living = false;
}

int Snake::length(void)
{
    return (int)body.size();
}

// Add new head point and delete old tail point
void Snake::move(void)
{
    body.push_back(next);
    body.erase(body.begin());
    calculateNext();
}

// Return the point in vector at index 'i'
Point Snake::pntAt(int i)
{
    if(i < 0 || i >= (int)body.size())
    {
        throw std::out_of_range(std::to_string(i));
    }
    return body[i];
}

void Snake::setDir(enum direction dir0)
{
    if(dir == dir0)
    {
        SNAKE_LOG("warning - snake is already travelling in that direction");
    }
    else
    {
        dir = dir0;
        calculateNext();
    }
}

// Private method definitions

// Calculate where the head of snake should be next based on
// its direction
void Snake::calculateNext(void)
{
    Point head = body[body.size() - 1];
    int nextX = head.getX();
    int nextY = head.getY();
    switch(dir)
    {
        case NORTH:
            --nextY;
            break;
        case EAST:
            ++nextX;
            break;
        case SOUTH:
            ++nextY;
            break;
        case WEST:
            --nextX;
            break;
        default:
            SNAKE_LOG("Invalid direction in method 'getNewHead'");
            break;
    }
    next = Point(nextX, nextY);
}
