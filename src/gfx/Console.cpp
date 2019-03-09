// A file to implement Console class methods

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <sstream>

// Custom class header file imports
#include "Button.h"
#include "Console.h"
#include "Font.h"
#include "GameState.h"
#include "Renderer.h"
#include "Score.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_CONSOLE)
#include <iostream>
#define CONSOLE_LOG(a) std::cout << "Console log: " << a << std::endl
#else
#define CONSOLE_LOG(a)
#endif

// Public method definitions

// Create a new console with viewport of specified location, width, and height
Console::Console(std::shared_ptr<Renderer> rnd, std::shared_ptr<Font> fnt,
                 SDL_Rect pos) :
UIElement(rnd, pos),
font(fnt),
helpButton(nullptr),
hiscore(nullptr),
okButton(nullptr),
playAgain(nullptr),
score(nullptr)
{
    std::string e = "Initialisation error - ";
    if(rnd == nullptr)
    {
        CONSOLE_LOG(e + "renderer was null");
    }
    else if(fnt == nullptr)
    {
        CONSOLE_LOG(e + "font was null");
    }
    else
    {
        if(!makePlayAgain(rnd, fnt))
        {
            CONSOLE_LOG(e + "play again txt failed");
        }
        if(!makeOkButton(rnd, fnt))
        {
            CONSOLE_LOG(e + "ok button failed");
        }
        makeHelpButton(rnd, fnt);
        score = std::make_unique<Score>(rnd, fnt, "Score: ", 0, 0, 0);
        hiscore = std::make_unique<Score>(rnd, fnt, "Highscore: ", 0, 0,
                                          score->getMaxTextH() + WINDOW_MARGIN);
    }
    CONSOLE_LOG("Console created");
}

Console::~Console(void)
{
    CONSOLE_LOG("Console destroyed");
}

// Handle mouse action within the console area
void Console::handleMouseEvent(GameState& gs, SDL_Event& e, SDL_Point mouse)
{
    if(gs.snakeAlive())
    {
        handleButtonEvent(helpButton, gs, e, mouse);
    }
    else
    {
        handleButtonEvent(okButton, gs, e, mouse);
    }
}

// Ensure buttons are not marked as hovered over
void Console::mouseOut(void)
{
    if(okButton) okButton->mouseOut();
    if(helpButton) helpButton->mouseOut();
}

// Private method definitions

// Handle mouse action relating to a UI button
void Console::handleButtonEvent(std::shared_ptr<Button> btn,
                                GameState& gs, SDL_Event& e, SDL_Point mouse)
{
    if(btn == nullptr)
    {
        CONSOLE_LOG("Could not handle mouse event - button is null");
    }
    else if(btn->overlaps(mouse))
    {
        btn->mouseOver();
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            btn->click(gs);
        }
    }
    else
    {
        btn->mouseOut();
    }
}

// Create new help button object.
void Console::makeHelpButton(std::shared_ptr<Renderer> rend,
                             std::shared_ptr<Font> font)
{
    SDL_Rect dm =  { pos.w - BUTTON_WIDTH - WINDOW_MARGIN,
                     WINDOW_MARGIN,
                     BUTTON_WIDTH,
                     BUTTON_HEIGHT };
    SDL_Color col = BUTTON_COLOR;
    SDL_Color hvCol = BUTTON_HOVER_COLOR;
    auto func = [](GameState& g) { g.pause(); };
    helpButton = std::make_shared<Button>(rend, font, dm, col, hvCol, "info",
                                          func);
}

// Create new ok button object. Return boolean to indicate success
bool Console::makeOkButton(std::shared_ptr<Renderer> rend,
                           std::shared_ptr<Font> font)
{
    SDL_Rect dm =  { (pos.w - BUTTON_WIDTH)/2,
                     UNDEFINED,
                     BUTTON_WIDTH,
                     BUTTON_HEIGHT };
    SDL_Color col = BUTTON_COLOR;
    SDL_Color hvCol = BUTTON_HOVER_COLOR;
    auto func = [](GameState& g) { g.reset(); };
    okButton = std::make_shared<Button>(rend, font, dm, col, hvCol, "OK",
                                        func);
    if(!okButton->setX((pos.w - okButton->getW())/2) || playAgain == nullptr ||
       !okButton->setY(playAgain->getY() + playAgain->getH() + LINE_GAP))
    {
        CONSOLE_LOG("Failed to make ok button - could not set button position");
        okButton = nullptr;
        return false;
    }
    return true;
}

// Create new text prompting replay. Return boolean to indicate success
bool Console::makePlayAgain(std::shared_ptr<Renderer> rend,
                            std::shared_ptr<Font> font)
{
    SDL_Color col = GAME_OVER_COLOR;
    playAgain = std::make_unique<Text>(rend, font, col,
                                       "Game Over! Play again?",
                                       0, WINDOW_MARGIN);
    if(!playAgain->setX((pos.w - playAgain->getW())/2))
    {
        CONSOLE_LOG("Failed to make play again text - could not be centered");
        playAgain = nullptr;
        return false;
    }
    return true;
}

// restore menu inviting user to play again
void Console::promptReplay(void)
{
    if(score) score->hide();
    if(hiscore) hiscore->hide();
    if(helpButton) helpButton->hide();
    if(playAgain) playAgain->restore();
    if(okButton) okButton->restore();
}

// Render all console content to the screen
void Console::render(void)
{
    std::shared_ptr<Renderer> lRend = rend.lock();
    if(lRend == nullptr)
    {
        CONSOLE_LOG("Could not render - renderer was already destroyed");
    }
    else
    {
        SDL_RenderSetViewport(lRend->getRaw(), &pos);
        if(score) score->show();
        if(hiscore) hiscore->show();
        if(playAgain) playAgain->show();
        if(okButton) okButton->show();
        if(helpButton) helpButton->show();
    }
}

// Render updated console content to the screen
void Console::render(GameState& gs)
{
    update(gs);
    render();
}

// Update console content based on the state of game logic
void Console::update(GameState& gs)
{
    if(!gs.snakeAlive())
    {
        promptReplay();
    }
    else
    {
        updateScores(gs);
        if(score) score->restore();
        if(hiscore) hiscore->restore();
        if(gs.gamePaused())
        {
            if(helpButton) helpButton->hide();
        }
        else
        {
            if(helpButton) helpButton->restore();
        }
        if(playAgain) playAgain->hide();
        if(okButton) okButton->hide();
    }
}

// Update score and high score values
void Console::updateScores(GameState& gs)
{
    int newScore = gs.getScore();
    if(score != nullptr)
    {
        if(newScore == 0 && score->getNum() != 0)
        {
            score->toZero();
        }
        else
        {
            score->update(newScore);
        }
    }
    if(hiscore) hiscore->update(gs.getHiscore());
}
