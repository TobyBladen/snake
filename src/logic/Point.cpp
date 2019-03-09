// A file to implement Point class methods

// Custom header file imports
#include "Point.h"

// Define macro debug log functionality
#include "log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_POINT)
#include <iostream>
#define POINT_LOG(a) std::cout << "Point log: " << a << std::endl
#else
#define POINT_LOG(a)
#endif

// Public method definitions

// Initialize x and y coordinates to 0 by default
Point::Point(void) : x(0), y(0)
{
    POINT_LOG("Point created");
}

// Initialize x and y coordinates with specified values
Point::Point(int x0, int y0) : x(x0), y(y0)
{
    POINT_LOG("Point created");
}

Point::~Point(void)
{
    POINT_LOG("Point destroyed");
}

int Point::getX(void)
{
    return x;
}

int Point::getY(void)
{
    return y;
}

// Return boolean to indicate if
// two point objects refer to the same space
bool Point::same(Point p)
{
    if(x == p.getX() && y == p.getY())
    {
        return true;
    }
    return false;
}
