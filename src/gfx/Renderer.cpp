// A file to implement Renderer class methods

// Standard header file imports
#include <iostream>
#include <SDL2/SDL.h>
#include <stdexcept>

// Custom class header file imports
#include "Renderer.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_RENDERER)
#include <iostream>
#define RENDERER_LOG(a) std::cout << "Renderer log: " << a << std::endl
#else
#define RENDERER_LOG(a)
#endif

// Public method definitions

// Create new SDL renderer object tied to window argument
Renderer::Renderer(SDL_Window* win) :
r(nullptr)
{
    r = SDL_CreateRenderer(win, -1,
                           (SDL_RENDERER_ACCELERATED |
                            SDL_RENDERER_PRESENTVSYNC));
    if(r == nullptr)
    {
        throw std::runtime_error("Failed to create SDL renderer");
    }
    RENDERER_LOG("Renderer created");
}

// Destroy the renderer with library-specific function
Renderer::~Renderer(void)
{
    if(r == nullptr)
    {
        RENDERER_LOG("Deconstructor found r set to null pointer");
    }
    else
    {
        SDL_DestroyRenderer(r);
        r = nullptr;
    }
    RENDERER_LOG("Renderer destroyed");
}

// Return raw pointer to the SDL renderer object
SDL_Renderer* Renderer::getRaw(void)
{
    RENDERER_LOG("Returning raw pointer to SDL renderer");
    return r;
}
