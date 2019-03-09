// A file to implement Window class methods

// Standard header file imports
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

// Custom class header file imports
#include "Renderer.h"
#include "Window.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_WINDOW)
#include <iostream>
#define WINDOW_LOG(a) std::cout << "Window log: " << a << std::endl
#else
#define WINDOW_LOG(a)
#endif

// Public method definitions

// Create a new SDL_Window object with specified name, width, and height
Window::Window(std::string winName0, int w, int h) :
pos({ SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h }),
winName(winName0)
{
    try
    {
        createSDLWin();
        WINDOW_LOG("Window created");
    }
    catch(std::runtime_error& e)
    {
        WINDOW_LOG(e.what());
        throw std::runtime_error("Window initialization failed");
    }
}

// Create a new SDL_Window object
// with specified name, position, width, and height
Window::Window(std::string winName0, SDL_Rect pos0) :
pos(pos0),
winName(winName0)
{
    try
    {
        createSDLWin();
        WINDOW_LOG("Window created");
    }
    catch(std::runtime_error& e)
    {
        WINDOW_LOG(e.what());
        throw std::runtime_error("Window initialization failed");
    }
}

Window::~Window(void)
{
    if(win == nullptr)
    {
        WINDOW_LOG("Destructor found SDL_Window pointer set to null");
    }
    else
    {
        SDL_DestroyWindow(win);
        win = nullptr;
    }
    WINDOW_LOG("Window destroyed");
}

// Return ptr to new renderer object tied to the window
std::unique_ptr<Renderer> Window::createRenderer(void)
{
    try
    {
        return std::make_unique<Renderer>(win);
    }
    catch(std::runtime_error& e)
    {
        WINDOW_LOG(e.what());
        throw std::runtime_error("Renderer initialization failed");
    }
}

int Window::getH(void)
{
    return pos.h;
}

int Window::getW(void)
{
    return pos.w;
}

int Window::getX(void)
{
    return pos.x;
}

int Window::getY(void)
{
    return pos.y;
}

// Private Method definitions

// Create raw SDL_Window object
void Window::createSDLWin(void)
{
    win = SDL_CreateWindow(winName.c_str(), pos.x, pos.y, pos.w, pos.h,
                           SDL_WINDOW_SHOWN);
    if(win == nullptr)
    {
        std::string msg = std::string("Failed to create window at location ") +
                          "x = '" + std::to_string(pos.x) +
                          "' and y = '" + std::to_string(pos.y) +
                          "' of width '" + std::to_string(pos.w) +
                          "' and height '" + std::to_string(pos.h) +
                          "' - " + SDL_GetError();
        throw std::runtime_error(msg);
    }
}
