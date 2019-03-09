#pragma once

// A class to wrap all library-dependent
// parts of the program that relate to I/O

// Standard header file imports
#include <memory>
#include <string>

// Forward declarations
class Board;
class Console;
class Font;
class GameState;
class OverlayMenu;
class Renderer;
union SDL_Event;
class Window;

// Primary class declaration
class Display
{
private:
    // Variables
    std::unique_ptr<Board> board;
    std::unique_ptr<Console> console;
    std::shared_ptr<Font> font;
    std::unique_ptr<OverlayMenu> info;
    std::shared_ptr<Renderer> rend;
    std::unique_ptr<Window> win;

    // Methods
    bool compatible(GameState&);
    void fontLibInit(void);
    void gfxLibInit(void);
    bool gridFits(int, int);
    void handleKeyPress(GameState&, SDL_Event&);
    void handleMouseEvent(GameState&, SDL_Event&);
    bool isMouseEvent(SDL_Event& e);

public:
    // Methods
    Display(std::string, const int, const int, const int);
    ~Display(void);
    void pollEvents(GameState&);
    void show(GameState&);
    void wait(int);
};
