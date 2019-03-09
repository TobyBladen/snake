// A file to implement Score class methods

// Standard header file imports
#include <memory>
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "Font.h"
#include "Renderer.h"
#include "Score.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_SCORE)
#include <iostream>
#define SCORE_LOG(a) std::cout << "Score log: " << a << std::endl
#else
#define SCORE_LOG(a)
#endif

// Public method definitions

// Create a representation of numerical score alongside a header
Score::Score(std::shared_ptr<Renderer> rnd, std::shared_ptr<Font> font0,
             std::string headerStr, int startingScore, unsigned int x,
             unsigned int y) :
UIElement(rnd, {(int)x, (int)y, TBD, TBD}),
cachedScore(startingScore),
font(font0),
scoreHeader(nullptr),
scoreVal(nullptr)
{
    if(rnd == nullptr)
    {
        SCORE_LOG("Initialization error - renderer is null");
    }
    else if(font0 == nullptr)
    {
        SCORE_LOG("Initialization error - font is null");
    }
    else
    {
        SDL_Color col = TEXT_COLOR;
        scoreHeader = std::make_unique<Text>(rnd, font0, col, headerStr, x, y);
        if(!makeScoreVal(rnd, font0, startingScore))
        {
            SCORE_LOG("Initialization error - failed to make score value");
        }
    }
    SCORE_LOG("Score created");
}

Score::~Score(void)
{
    SCORE_LOG("Score destroyed");
}

// Get the highest point of either text element
int Score::getMaxTextH(void)
{
    int max;
    if(scoreHeader == nullptr)
    {
        max = scoreVal ? scoreVal->getH() : 0;
    }
    else if(!scoreVal)
    {
        max = scoreHeader->getH();
    }
    else
    {
        int a = scoreHeader->getH();
        int b = scoreVal->getH();
        max = a > b ? a : b;
    }
    return max;
}

int Score::getNum(void)
{
    return cachedScore;
}

// Update the user score. Return boolean to indicate success
bool Score::update(int newScore)
{
    bool success = false;
    if(newScore <= cachedScore) success = true;
    else
    {
        std::shared_ptr<Renderer> lRend = rend.lock();
        if(!lRend) SCORE_LOG("Could not update - rend destroyed");
        else
        {
            std::shared_ptr<Font> lFont = font.lock();
            if(!lFont) SCORE_LOG("Could not update - font destroyed");
            else if(!makeScoreVal(lRend, lFont, newScore))
            {
                SCORE_LOG("Could not update - failed to make score value text");
            }
            else
            {
                cachedScore = newScore;
                success = true;
            }
        }
    }
    return success;
}

// Reset user score to zero. Return boolean to indicate success
bool Score::toZero(void)
{
    bool success = false;
    std::shared_ptr<Renderer> lRend = rend.lock();
    if(!lRend) SCORE_LOG("Could not reset score - renderer destroyed");
    else
    {
        std::shared_ptr<Font> lFont = font.lock();
        if(!lFont) SCORE_LOG("Could not reset score - font destroyed");
        else if(!makeScoreVal(lRend, lFont, 0))
        {
            SCORE_LOG("Could not reset score - failed to make value text");
        }
        else
        {
            cachedScore = 0;
            success = true;
        }
    }
    return success;
}

// Private method definitions

// Make text representation of score count
bool Score::makeScoreVal(std::shared_ptr<Renderer> rnd,
                         std::shared_ptr<Font> fnt, int val)
{
    if(scoreHeader == nullptr)
    {
        SCORE_LOG("Failed to make score value  - header was null");
        return false;
    }
    SDL_Color col = TEXT_COLOR;
    scoreVal = std::make_unique<Text>(rnd, fnt, col, std::to_string(val),
                                      scoreHeader->getW() + SCORE_MARGIN,
                                      scoreHeader->getY());
    return true;
}

// Render all text elements to the screen
void Score::render(void)
{
    if(scoreHeader) scoreHeader->show();
    if(scoreVal) scoreVal->show();
}

// Render all text elements to the screen
void Score::render(GameState& gs)
{
    SCORE_LOG("Warning: game state argument will be ignored in rendering");
    (void)(gs);
    render();
}
