// A file to implement Rect class methods

// Custom class header file imports
#include "Rect.h"
#include "Renderer.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_RECT)
#include <iostream>
#define RECT_LOG(a) std::cout << "Rect log: " << a << std::endl
#else
#define RECT_LOG(a)
#endif

// Public method definitions

// Create new filled rectangle with specified location, dimensions, and colour
Rect::Rect(std::shared_ptr<Renderer> rend, SDL_Rect pos, SDL_Color col0) :
UIElement(rend, pos),
col(col0)
{
    RECT_LOG("Rect created");
}

Rect::~Rect(void)
{
    RECT_LOG("Rect destroyed");
}

// Private method definitions

// Draw filled rectangle to the viewport
void Rect::render(void)
{
    std::shared_ptr<Renderer> lRend = rend.lock();
    if(lRend == nullptr)
    {
        RECT_LOG("Could not render - Renderer was already destroyed");
    }
    else
    {
        SDL_SetRenderDrawColor(lRend->getRaw(), col.r, col.g, col.b, col.a);
        SDL_RenderFillRect(lRend->getRaw(), &pos);
    }
}

// Draw filled rectangle to the viewport
void Rect::render(GameState& gs)
{
    RECT_LOG("Warning: game state argument will be ignored in rendering");
    (void)(gs);
    render();
}
