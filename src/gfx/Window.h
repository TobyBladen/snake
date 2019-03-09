#pragma once

// A class to wrap SDL_Window object

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Forward declarations
class Renderer;

// Primary class declaration
class Window
{
private:
    // Variables
    SDL_Rect pos;
    std::string winName;
    SDL_Window* win;

    // Methods
    void createSDLWin(void);

public:
    // Methods
    Window(std::string, int, int);
    Window(std::string, SDL_Rect);
    ~Window(void);
    std::unique_ptr<Renderer> createRenderer(void);
    int getH(void);
    int getW(void);
    int getX(void);
    int getY(void);
};
