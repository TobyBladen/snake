#pragma once

// A class to represent a filled rectangle

// Standard header file imports
#include "SDL2/SDL.h"

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class GameState;
class Renderer;

// Primary class declaration
class Rect : public UIElement
{
private:
    // Variables
    SDL_Color col;
    // Methods
    void render(void);
    void render(GameState&);
public:
    // Methods
    Rect(std::shared_ptr<Renderer>, SDL_Rect, SDL_Color);
    ~Rect(void);
};
