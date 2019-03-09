#pragma once

// A class to wrap raw SDL_Renderer object pointer

// Standard header file imports
#include <string>

// Forward declarations
struct SDL_Renderer;
struct SDL_Window;

// Primary class declaration
class Renderer
{
private:
    // Variables
    SDL_Renderer* r;

public:
    // Methods
    Renderer(SDL_Window*);
    ~Renderer(void);
    SDL_Renderer* getRaw(void);
};
