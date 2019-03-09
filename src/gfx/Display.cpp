// A file to implement Display class methods

// Standard header file imports
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#if defined(__APPLE__)
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL2/SDL_ttf.h>
#endif
#include <stdexcept>

// Custom class header file imports
#include "Board.h"
#include "Console.h"
#include "Display.h"
#include "Font.h"
#include "GameState.h"
#include "OverlayMenu.h"
#include "Renderer.h"
#include "Window.h"

// Import game text content
#include "content.h"
// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_DISPLAY)
#include <iostream>
#define DISPLAY_LOG(a) std::cout << "Display log: " << a << std::endl
#else
#define DISPLAY_LOG(a)
#endif

// Public method definitions

// Initialize a new window-based display. The window is of specified height,
// width, and name. It is divided into two at specified location 'boardHeight'
Display::Display(std::string winName, const int winWidth, const int winHeight,
                 const int boardHeight) :
board(nullptr),
console(nullptr),
font(nullptr),
info(nullptr),
rend(nullptr),
win(nullptr)
{
    try
    {
        gfxLibInit();
        fontLibInit();
        win = std::make_unique<Window>(winName, winWidth, winHeight);
        rend = win->createRenderer();
        font = std::make_shared<Font>(FONT, FONT_SIZE);
        SDL_Rect csDm = {0, 0, win->getW(), win->getH() - boardHeight};
        console = std::make_unique<Console>(rend, font, csDm);
        SDL_Rect bdDm = {0, console->getH(), win->getW(), boardHeight};
        board = std::make_unique<Board>(rend, bdDm);
        std::vector<std::string> infoStrs = {MAIN_TITLE, INSTRUCT, CPYRT};
        SDL_Rect infoDm = {0, 0, win->getW(), win->getH()};
        info = std::make_unique<OverlayMenu>(rend, font, infoStrs, infoDm);
        info->hide();
        DISPLAY_LOG("Display created");
    }
    catch(std::runtime_error& e)
    {
        DISPLAY_LOG(e.what());
        throw std::runtime_error("Display initialization failed");
    }
}

// Manually free all class attributes
// before calling gfx and font library quit functions
Display::~Display(void)
{
    info.reset();
    board.reset();
    console.reset();
    font.reset();
    rend.reset();
    win.reset();
    TTF_Quit();
    SDL_Quit();
    DISPLAY_LOG("Display destroyed");
}

// Check for any user input
void Display::pollEvents(GameState& gs)
{
    SDL_Event e;
    bool dirChanged = false;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            gs.quit();
        }
        else if(isMouseEvent(e))
        {
            handleMouseEvent(gs, e);
        }
        else if(e.type == SDL_KEYDOWN)
        {
            if(gs.snakeAlive() && !dirChanged)
            {
                handleKeyPress(gs, e);
                dirChanged = true;
            }
        }
    }
}

// Generate graphical representation of a compatible game state
void Display::show(GameState& gs)
{
    if(!compatible(gs))
    {
        DISPLAY_LOG("Cannot show - game state is incompatible with display.");
    }
    else
    {
        if(gs.gamePaused())
        {
            info->restore();
        }
        else
        {
            info->hide();
        }
        SDL_SetRenderDrawColor(rend->getRaw(), 0, 0, 0, 0);
        SDL_RenderClear(rend->getRaw());
        console->show(gs);
        board->show(gs);
        info->show();
        SDL_RenderPresent(rend->getRaw());
    }
}

// Private method definitions

// Determine if the game state is
// suitable to be printed by display or not
bool Display::compatible(GameState& gs)
{
    int gridSize = gs.getGridSize();
    int winWidth = win->getW();
    int boardHeight = board->getH();
    if(!gridFits(winWidth, gridSize))
    {
        DISPLAY_LOG("Grid size '" + std::to_string(gridSize) +
                    "' is incompatible with window width '" +
                    std::to_string(winWidth) + "'.");
    }
    else if(!gridFits(boardHeight, gridSize))
    {
        DISPLAY_LOG("Grid size '" + std::to_string(gridSize) +
                    "' is incompatible with board height '" +
                    std::to_string(boardHeight) + "'.");
    }
    else
    {
        return true;
    }
    return false;
}

// Try to initialize font library
void Display::fontLibInit(void)
{
    if(TTF_Init() == -1)
    {
        std::string msg = "SDL TTF initialisation failed - ";
        msg += TTF_GetError();
        throw std::runtime_error(msg);
    }
}

// Try to initialize graphics library
void Display::gfxLibInit(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::string msg = "SDL initialisation failed - ";
        msg += SDL_GetError();
        throw std::runtime_error(msg);
    }
    else if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        DISPLAY_LOG("Could not enable linear texture filtering");
    }
}

// Return boolean to indicate whether a grid size fits a given side dimension
bool Display::gridFits(int side, int grdSz)
{
    if(grdSz > side || side % (grdSz + 2) != 0)
    {
        return false;
    }
    return true;
}

// Handle keyboard user input
void Display::handleKeyPress(GameState& gs, SDL_Event& e)
{
    enum direction dir = gs.getSnakeDir();
    switch(e.key.keysym.sym)
    {
        case SDLK_UP:
            if(dir == EAST || dir == WEST) gs.setSnakeDir(NORTH);
            break;
        case SDLK_LEFT:
            if(dir == NORTH || dir == SOUTH) gs.setSnakeDir(WEST);
            break;
        case SDLK_DOWN:
            if(dir == EAST || dir == WEST) gs.setSnakeDir(SOUTH);
            break;
        case SDLK_RIGHT:
            if(dir == NORTH || dir == SOUTH) gs.setSnakeDir(EAST);
            break;
        default:
            DISPLAY_LOG("Misc key pressed");
            break;
    }
}

// Handle any form of mouse event from the player
void Display::handleMouseEvent(GameState& gs, SDL_Event& e)
{
    SDL_Point mouse;
    SDL_GetMouseState(&(mouse.x), &(mouse.y));
    if(gs.gamePaused())
    {
        info->handleMouseEvent(gs, e, mouse);
    }
    else if(mouse.y < console->getH())
    {
        console->handleMouseEvent(gs, e, mouse);
    }
    else
    {
        console->mouseOut();
    }
}

// Return boolean to indicate if the type an SDL_Event is mouse-related or not
bool Display::isMouseEvent(SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION ||
       e.type == SDL_MOUSEBUTTONDOWN ||
       e.type == SDL_MOUSEBUTTONUP)
    {
        return true;
    }
    return false;
}

// Delay for a given amount of time in milliseconds
void Display::wait(int ms)
{
    SDL_Delay(ms);
}
