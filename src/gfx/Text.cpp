// A file to implement Text class methods

// Standard header file imports
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#if defined(__APPLE__)
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL2/SDL_ttf.h>
#endif

// Custom class header file imports
#include "Font.h"
#include "Renderer.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_TEXT)
#include <iostream>
#define TEXT_LOG(a) std::cout << "Text log: " << a << std::endl
#else
#define TEXT_LOG(a)
#endif

// Public method definitions

// Generate texture for a specified string in a specified color and font.
// Additionally save the text's position
Text::Text(std::shared_ptr<Renderer> rnd, std::shared_ptr<Font> font,
           SDL_Color col, std::string str0, unsigned int x, unsigned int y) :
UIElement(rnd, { (int) x, (int) y, TBD, TBD } ),
str(str0),
texture(nullptr)
{
    if(font == nullptr)
    {
        TEXT_LOG("Could not complete text initialization - font is null");
    }
    else
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font->getRaw(), str.c_str(),
                                                    col);
        if(surface == nullptr)
        {
            TEXT_LOG(std::string("Failed to render text surface - ") +
                     TTF_GetError());
        }
        else
        {
            getTexture(rnd, *surface);
            SDL_FreeSurface(surface);
        }
    }
    TEXT_LOG("Text created");
}

Text::~Text(void)
{
    if(texture == nullptr)
    {
        TEXT_LOG("Deconstructor found texture set to null pointer");
    }
    else
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    TEXT_LOG("Text destroyed");
}

// Return underlying string representation of text object
std::string Text::getStr(void)
{
    return str;
}

// Private method definitions

// Generate an SDL texture from text surface and hold it as member
void Text::getTexture(std::shared_ptr<Renderer> rend, SDL_Surface& surface)
{
    texture = SDL_CreateTextureFromSurface(rend->getRaw(), &surface);
    if(texture == nullptr)
    {
        TEXT_LOG(std::string("Failed to create texture from text surface - ") +
                 SDL_GetError());
    }
    else
    {
        pos.w = surface.w;
        pos.h = surface.h;
    }
}

// Copy generated texture to the viewport
void Text::render(void)
{
    if(texture == nullptr)
    {
        TEXT_LOG("Could not render - texture is null");
    }
    else
    {
        std::shared_ptr<Renderer> lRend = rend.lock();
        if(lRend == nullptr)
        {
            TEXT_LOG("Could not render - Renderer was already destroyed");
        }
        else
        {
            SDL_RenderCopy(lRend->getRaw(), texture, nullptr, &pos);
        }
    }
}

// Copy generated texture to the viewport
void Text::render(GameState& gs)
{
    TEXT_LOG("Warning: game state argument will be ignored in rendering");
    (void)(gs);
    render();
}
