#pragma once

// A class to bundle a string of text
// with its position and textural representation

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class Font;
class GameState;
class Renderer;

// Primary class declaration
class Text : public UIElement
{
private:
    // Variables
    std::string str;
    SDL_Texture* texture;

    // Methods
    void getTexture(std::shared_ptr<Renderer>, SDL_Surface&);
    void render(void);
    void render(GameState&);

public:
    // Methods
    Text(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
         SDL_Color, std::string, unsigned int, unsigned int);
    ~Text(void);
    std::string getStr(void);
};
