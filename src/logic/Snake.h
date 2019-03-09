#pragma once

// A class to represent a snaking line of point objects

// Standard header file imports
#include <vector>

// Defines
enum direction { NORTH, EAST, SOUTH, WEST };

// Forward declarations
class Point;

// Primary class declaration
class Snake
{
private:
    // Variables
    std::vector<Point> body;
    enum direction dir;
    bool living;
    Point next;
    // Methods
    void calculateNext(void);

public:
    // Methods
    Snake(const int);
    ~Snake();
    bool alive(void);
    enum direction getDir(void);
    Point getNext(void);
    void grow(void);
    void kill(void);
    int length(void);
    void move(void);
    Point pntAt(int i);
    void setDir(enum direction);
};
