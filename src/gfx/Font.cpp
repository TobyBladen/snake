// A file to implement Font class methods

// Standard header file imports
#include <iostream>
#if defined(__APPLE__)
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL2/SDL_ttf.h>
#endif
#include <stdexcept>
#include <string>

// Custom class header file imports
#include "Font.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_FONT)
#include <iostream>
#define FONT_LOG(a) std::cout << "Font log: " << a << std::endl
#else
#define FONT_LOG(a)
#endif

// Public method definitions

// Get TTF Font from specified file path at specified size
Font::Font(std::string fontFPath, unsigned int fontSize)
{
    f = TTF_OpenFont(fontFPath.c_str(), fontSize);
    if(f == nullptr)
    {
        std::string msg = "Failed to load TTF font from filepath '" +
                          fontFPath + "': " + TTF_GetError();
        throw std::runtime_error(msg);
    }
    FONT_LOG("Font created");
}

// Close the font with library-specific function
Font::~Font(void)
{
    if(f == nullptr)
    {
        FONT_LOG("Deconstructor found f set to null pointer");
    }
    else
    {
        TTF_CloseFont(f);
        f = nullptr;
    }
    FONT_LOG("Font destroyed");
}

// Return raw pointer to TTF_font object
TTF_Font* Font::getRaw(void)
{
    FONT_LOG("Returning raw pointer to TTF Font");
    return f;
}
