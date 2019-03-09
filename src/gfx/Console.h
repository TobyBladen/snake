#pragma once

// A class to represent the upper viewport of screen containing text info

// Standard header file imports
#include <memory>

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class Button;
class Font;
class GameState;
class Renderer;
class Score;
struct SDL_Renderer;
class Text;

// Primary class declaration
class Console : public UIElement
{
private:
    // Variables
    std::weak_ptr<Font> font;
    std::shared_ptr<Button> helpButton;
    std::unique_ptr<Score> hiscore;
    std::shared_ptr<Button> okButton;
    std::unique_ptr<Text> playAgain;
    std::unique_ptr<Score> score;
    // Methods
    void handleButtonEvent(std::shared_ptr<Button>, GameState&, SDL_Event&,
                           SDL_Point);
    void makeHelpButton(std::shared_ptr<Renderer>, std::shared_ptr<Font>);
    bool makeOkButton(std::shared_ptr<Renderer>, std::shared_ptr<Font>);
    bool makePlayAgain(std::shared_ptr<Renderer>, std::shared_ptr<Font>);
    void promptReplay(void);
    void render(void);
    void render(GameState&);
    void update(GameState&);
    void updateScores(GameState&);

public:
    // Methods
    Console(std::shared_ptr<Renderer>, std::shared_ptr<Font>, SDL_Rect);
    ~Console();
    void handleMouseEvent(GameState&, SDL_Event&, SDL_Point);
    void mouseOut(void);
};
