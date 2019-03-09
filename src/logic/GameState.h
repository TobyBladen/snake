#pragma once

// A class to bring together all parts of the game logic

// Standard header file imports
#include <memory>

// Custom class header file imports
#include "Point.h"
#include "Snake.h"

// Defines
enum difficulty { UNDEFINED, EASY, MEDIUM, HARD, BRUTAL };

// Primary class declaration
class GameState
{
private:
    // Variables
    enum difficulty difficulty;
    Point food;
    const int gridSize;
    int hiscore;
    bool paused;
    bool play;
    std::unique_ptr<Snake> snake;
    const int snakeStLen;

    // Methods
    bool bodyCollision(Point head);
    void checkArgs(const int, const int);
    bool foodCollision(Point head);
    Point randomPoint(void);
    bool wallCollision(Point head);

public:
    // Methods
    GameState(const int, const int, int);
    ~GameState(void);
    bool gamePaused(void);
    enum difficulty getDifficulty(void);
    Point getFood(void);
    int getGridSize(void);
    int getHiscore(void);
    int getScore(void);
    enum direction getSnakeDir(void);
    int getSnakeLength(void);
    Point getSnakePntAt(int);
    int getSnakeStLen(void);
    void moveSnake(void);
    void pause(void);
    bool playing(void);
    void quit(void);
    void reset(void);
    void resume(void);
    void setDifficulty(enum difficulty);
    void setFood(Point);
    void setSnakeDir(enum direction);
    bool snakeAlive(void);
};
