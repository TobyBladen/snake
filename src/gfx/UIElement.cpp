// A file to implement UIElement class methods

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "Renderer.h"
#include "UIElement.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_UI_ELEMENT)
#include <iostream>
#define UI_ELEMENT_LOG(a) std::cout << "UI Element log: " << a << std::endl
#else
#define UI_ELEMENT_LOG(a)
#endif

// Public method definitions

// Create new UI element tied to a specific renderer and position in viewport
UIElement::UIElement(std::shared_ptr<Renderer> rend0, SDL_Rect pos0) :
concealed(false),
pos(pos0),
rend(rend0)
{
    UI_ELEMENT_LOG("UI Element created");
}

UIElement::~UIElement(void)
{
    UI_ELEMENT_LOG("UI Element destroyed");
}

// Return height of UI element
int UIElement::getH(void)
{
    return pos.h;
}

// Return width of UI element
int UIElement::getW(void)
{
    return pos.w;
}

// Return x coordinate of UI element position
int UIElement::getX(void)
{
    return pos.x;
}

// Return y coordinate of UI element position
int UIElement::getY(void)
{
    return pos.y;
}

// Return boolean to show if element is currently hidden or not
bool UIElement::hidden(void)
{
    return concealed;
}

// Flag UI element as hidden
void UIElement::hide(void)
{
    concealed = true;
}

// Return boolean to indicate whether point p
// is inside the area of the UI element or not
bool UIElement::overlaps(SDL_Point p)
{
    if(p.x > pos.x && p.x < pos.x + pos.w &&
       p.y > pos.y && p.y < pos.y + pos.h)
    {
        return true;
    }
    return false;
}

// Flag UI element as shown
void UIElement::restore(void)
{
    concealed = false;
}

// Set x coordinate of UI element position if argument is greater than zero
// Return boolean to indicate success
bool UIElement::setX(int x0)
{
    if(x0 < 0)
    {
        UI_ELEMENT_LOG(std::string("Asked to set X position ") +
                       "to less than zero: " +
                       std::to_string(x0));
        return false;
    }
    pos.x = x0;
    return true;
}

// Set y coordinate of UI element position if argument is greater than zero
// Return boolean to indicate success
bool UIElement::setY(int y0)
{
    if(y0 < 0)
    {
        UI_ELEMENT_LOG(std::string("Asked to set Y position ") +
                       "to less than zero: " +
                       std::to_string(y0));
        return false;
    }
    pos.y = y0;
    return true;
}

// Display the UI element to screen
void UIElement::show(void)
{
    if(!concealed) render();
}

// Display the UI element to screen using data from the game logic
void UIElement::show(GameState& gs)
{
    if(!concealed) render(gs);
}
