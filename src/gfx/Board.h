#pragma once

// A class to represent the lower viewport of
// screen showing snake, food, and walls

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class GameState;
class Renderer;

// Primary class declaration
class Board : public UIElement
{
private:
    // Methods
    void drawFood(std::shared_ptr<Renderer>, GameState&, const int, const int);
    void drawSnake(std::shared_ptr<Renderer>, GameState&, const int, const int);
    void drawWalls(std::shared_ptr<Renderer>, const int, const int);
    void render(void);
    void render(GameState& gs);

public:
    // Methods
    Board(std::shared_ptr<Renderer>, SDL_Rect);
    ~Board(void);
};
