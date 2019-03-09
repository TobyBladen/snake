#pragma once

// A class to hold a single set of 2D (x, y) coordinates

// Primary class declaration
class Point
{
private:
    // Variables
    int x, y;
public:
    // Methods
    Point(void);
    Point(int, int);
    ~Point(void);
    int getX(void);
    int getY(void);
    bool same(Point);
};
