#pragma once

// A class to represent a part of the UI or menus

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>

// Forward declarations
class GameState;
class Renderer;

// Primary class declaration
class UIElement
{
private:
    // Variables
    bool concealed;
    // Methods
    virtual void render(void) = 0;
    virtual void render(GameState&) = 0;

protected:
    // Variables
    SDL_Rect pos;
    std::weak_ptr<Renderer> rend;

public:
    // Methods
    UIElement(std::shared_ptr<Renderer>, SDL_Rect);
    virtual ~UIElement(void);
    int getH(void);
    int getW(void);
    int getX(void);
    int getY(void);
    bool hidden(void);
    void hide(void);
    bool overlaps(SDL_Point);
    void restore(void);
    bool setX(int);
    bool setY(int);
    void show(void);
    void show(GameState&);
};
