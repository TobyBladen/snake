#pragma once

// A class to represent a UI button

// Standard header file imports
#include <functional>
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "Rect.h"
#include "UIElement.h"

// Forward declarations
class Font;
class GameState;
class Text;

// Primary class declaration
class Button : public UIElement
{
private:
    // Variables
    Rect bg;
    std::unique_ptr<Text> btnTxt;
    std::function<void(GameState&)> callback;
    bool hover;
    Rect hoverBg;

    // Methods
    bool centerBtnTxt(void);
    bool createBtnTxt(std::shared_ptr<Font>, std::string str);
    void render(void);
    void render(GameState&);
    bool validStr(std::string);

public:
    // Methods
    Button(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
         SDL_Rect, SDL_Color, SDL_Color, std::string,
         std::function<void(GameState&)>);
    ~Button(void);
    void click(GameState&);
    void mouseOut(void);
    void mouseOver(void);
    bool setX(int);
    bool setY(int);
};
