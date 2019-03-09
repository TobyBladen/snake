// A file to implement Button class methods

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "Button.h"
#include "GameState.h"
#include "Rect.h"
#include "Renderer.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_BUTTON)
#include <iostream>
#define BTN_LOG(a) std::cout << "Button log: " << a << std::endl
#else
#define BTN_LOG(a)
#endif

// Public method definitions

// Create a new UI button with specified position, colour, hover colour, text
// and press functionality
Button::Button(std::shared_ptr<Renderer> rend, std::shared_ptr<Font> font,
               SDL_Rect pos, SDL_Color col, SDL_Color hoverCol,
               std::string str, std::function<void(GameState&)> callback0) :
UIElement(rend, pos),
bg(rend, pos, col),
btnTxt(nullptr),
callback(callback0),
hover(false),
hoverBg(rend, pos, hoverCol)
{
    if(!createBtnTxt(font, str))
    {
        BTN_LOG(std::string("Could not create button text from string '") +
                   str + "'.");
    }
    BTN_LOG("Button created");
}

Button::~Button(void)
{
    BTN_LOG("Button destroyed");
}

// Set x coordinate of button and all component parts if argument is greater
// than zero. Return boolean to indicate success
bool Button::setX(int x0)
{
    bool success = false;
    if(x0 < 0)
    {
        BTN_LOG(std::string("Asked to set X position to less than zero: ") +
                   std::to_string(x0));
    }
    else
    {
        pos.x = x0;
        if(!bg.setX(x0))
        {
            BTN_LOG(std::string("Failed to set bg x to ") + std::to_string(x0));
        }
        else if(!hoverBg.setX(x0))
        {
            BTN_LOG(std::string("Failed to set hover bg x to ") +
                    std::to_string(x0));
        }
        else if(btnTxt != nullptr &&
                !btnTxt->setX(pos.x + ((pos.w - btnTxt->getW())/2)))
        {
            BTN_LOG("Failed to recenter button text after setting x");
        }
        else
        {
            success = true;
        }
    }
    return success;
}

// Set y coordinate of button and all component parts if argument is greater
// than zero. Return boolean to indicate success
bool Button::setY(int y0)
{
    bool success = false;
    if(y0 < 0)
    {
        BTN_LOG(std::string("Asked to set Y position to less than zero: ") +
                   std::to_string(y0));
    }
    else
    {
        pos.y = y0;
        if(!bg.setY(y0))
        {
            BTN_LOG(std::string("Failed to set bg y to ") + std::to_string(y0));
        }
        else if(!hoverBg.setY(y0))
        {
            BTN_LOG(std::string("Failed to set hover bg y to ") +
                    std::to_string(y0));
        }
        else if(btnTxt != nullptr &&
                !btnTxt->setY(pos.y + ((pos.h - btnTxt->getH())/2)))
        {
            BTN_LOG("Failed to recenter button text after setting y");
        }
        else
        {
            success = true;
        }
    }
    return success;
}

// Flag that the mouse is hovering over the button
void Button::mouseOver(void)
{
    hover = true;
}

// Flag that the mouse is not hovering over the button
void Button::mouseOut(void)
{
    hover = false;
}

// Call button click functionality in form of callback
void Button::click(GameState& gs)
{
    callback(gs);
}

// Private method definitions

// Center text in the middle of the button area.
// Return boolean to indicate success
bool Button::centerBtnTxt(void)
{
    bool centered = false;
    if(!btnTxt->setX(pos.x + ((pos.w - btnTxt->getW())/2)))
    {
        BTN_LOG("Failed to center button text x position");
    }
    else
    {
        centered = btnTxt->setY(pos.y + ((pos.h - btnTxt->getH())/2));
        if(!centered)
        {
            BTN_LOG("Failed to center button text y position");
        }
    }
    return centered;
}

// Attempt to make text element from specified font and string
// Return boolean to indicate success
bool Button::createBtnTxt(std::shared_ptr<Font> font, std::string str)
{
    bool success = false;
    if(validStr(str))
    {
        std::shared_ptr<Renderer> lRend = rend.lock();
        if(lRend == nullptr)
        {
            BTN_LOG("Renderer was already destroyed");
        }
        else
        {
            SDL_Color txtCol = BUTTON_TEXT_COLOR;
            btnTxt = std::make_unique<Text>(lRend, font, txtCol, str,
                                            TBD, TBD);
            if(!centerBtnTxt())
            {
                BTN_LOG("Resetting button text to null - Failed to center");
                btnTxt.reset(nullptr);
            }
            else
            {
                success = true;
            }
        }
    }
    return success;
}

// Copy all visual elements of button to the screen
void Button::render(void)
{
    if(hover)
    {
        hoverBg.show();
    }
    else
    {
        bg.show();
    }
    if(btnTxt) btnTxt->show();
}

// Copy all visual elements of button to the screen
void Button::render(GameState& gs)
{
    BTN_LOG("Warning: game state argument will be ignored");
    (void)(gs);
    render();
}

// Return boolean to indicate if string argument is valid rather than null
bool Button::validStr(std::string str)
{
    if(str == "")
    {
        BTN_LOG("String argument is null");
        return false;
    }
    return true;
}
