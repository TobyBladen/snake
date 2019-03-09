// A file to implement Paragraph class methods

// Standard header file imports
#include <memory>

// Custom class header file imports
#include "Font.h"
#include "Paragraph.h"
#include "Renderer.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_PARAGRAPH)
#include <iostream>
#define PARAGRAPH_LOG(a) std::cout << "Paragraph log: " << a << std::endl
#else
#define PARAGRAPH_LOG(a)
#endif

// Public method definitions

// Create new paragraph with specified x, y, width, font, colour, and content
Paragraph::Paragraph(std::shared_ptr<Renderer> rnd, std::shared_ptr<Font> font,
                     SDL_Color col, std::string str0, unsigned int x,
                     unsigned int y, unsigned int w) :
UIElement(rnd, { (int) x, (int) y, (int) w, TBD }),
str(str0)
{
    std::string e = "Initialization error - ";
    if(str == "") PARAGRAPH_LOG(e + "string arg is null");
    else if(!rnd) PARAGRAPH_LOG(e + "renderer is null");
    else if(!font) PARAGRAPH_LOG(e + "font is null");
    else if(!wordsInit(rnd, font, col)) PARAGRAPH_LOG(e + "words init failed");
    else
    {
        auto last = words.back();
        pos.h = last->getY() - pos.y + last->getH();
    }
    PARAGRAPH_LOG("Paragraph created");
}

Paragraph::~Paragraph()
{
    PARAGRAPH_LOG("Paragraph destroyed");
}

// Update the y pos of the whole paragraph and ensure each line of text
// maintains its current offset
bool Paragraph::setY(int y0)
{
    if(y0 < 0)
    {
        PARAGRAPH_LOG(std::string("Asked to set para Y pos to less than 0: ") +
                       std::to_string(y0));
    }
    else if(!calculateWordsY(y0))
    {
        PARAGRAPH_LOG(std::string("Failed to set para Y to ") +
                      std::to_string(y0) + " - issue calculating words' y pos");
    }
    else
    {
        pos.y = y0;
        return true;
    }
    return false;
}

// Private method definitions

// Calculate and set the y pos of an individual word at index i based on the
// starting y pos of whole para. Return boolean to indicate success
bool Paragraph::calculateWordY(int i, int paraNewY)
{
    int wdOffset = words[i]->getY() - pos.y;
    int newY = paraNewY + wdOffset;
    if(!words[i]->setY(newY))
    {
        PARAGRAPH_LOG(std::string("Failed to set y position to '") +
                      std::to_string(newY) + "' for word '" +
                      words[i]->getStr() + "' at index '" +
                      std::to_string(i) + "'.");
        return false;
    }
    return true;
}

// Calculate and set the y pos of all words in the para.
// Return boolean to indicate success
bool Paragraph::calculateWordsY(int paraNewY)
{
    for(int i = 0; i < (int)words.size(); i++)
    {
        if(words[i] == nullptr)
        {
            PARAGRAPH_LOG(std::string("Failed to calculate y pos - ") +
                          "word at index " + std::to_string(i) + " is null");
            return false;
        }
        else if(!calculateWordY(i, paraNewY))
        {
            PARAGRAPH_LOG(std::string("Failed to calculate word's y pos - ") +
                          "at index " + std::to_string(i));
            return false;
        }
    }
    return true;
}

// Print all words in the paragraph to the screen
void Paragraph::render(void)
{
    for(auto word : words)
    {
        if(word) word->show();
    }
}

// Print all words in the paragraph to the screen
void Paragraph::render(GameState& gs)
{
    PARAGRAPH_LOG("Warning: game state argument will be ignored in rendering");
    (void)(gs);
    render();
}

// Convert a string into a Text object and return it
std::unique_ptr<Text> Paragraph::str2Txt(std::shared_ptr<Renderer> rnd,
                                         std::shared_ptr<Font> font,
                                         SDL_Color col, std::string str)
{
    auto t = std::make_unique<Text>(rnd, font, col, str, TBD, TBD);
    if(words.empty())
    {
        t->setX(pos.x + PARA_INDENT);
        t->setY(pos.y);
    }
    else
    {
        auto last = words.back();
        int lastX = last->getX();
        int lastW = last->getW();
        int wordEnd = lastX + lastW + t->getW();
        if(wordEnd > pos.w)
        {
            t->setX(pos.x);
            t->setY(last->getY() + last->getH() + LINE_GAP);
        }
        else
        {
            t->setX(lastX + lastW);
            t->setY(last->getY());
        }
    }
    return t;
}

// Get the Text object equivalent for a word and add it to the words vector
// Return boolean to indicate success.
bool Paragraph::wordInit(std::shared_ptr<Renderer> rnd,
                         std::shared_ptr<Font> font, SDL_Color col,
                         std::string word)
{
    auto t = str2Txt(rnd, font, col, word);
    if(t == nullptr)
    {
        PARAGRAPH_LOG(std::string("Could not initialize word '")
                      + word + "' - text representation was null");
                return false;
    }
    words.push_back(std::move(t));
    return true;
}

// Deduce word boundaries in the paragraph string and initilise each individual
// word. Return boolean to indicate success.
bool Paragraph::wordsInit(std::shared_ptr<Renderer> rnd,
                          std::shared_ptr<Font> font, SDL_Color col)
{
    int wordSt = 0;
    for(int i = 0; i < (int)str.length(); i++)
    {
        if(str[i] == ' ')
        {
            std::string word = str.substr(wordSt, i + 1 - wordSt);
            if(!wordInit(rnd, font, col, word))
            {
                PARAGRAPH_LOG("Failed to initialize words vector");
                return false;
            }
            wordSt = i + 1;
        }
    }
    if(wordSt != (int)str.length())
    {
        std::string word = str.substr(wordSt, str.length());
        if(!wordInit(rnd, font, col, word))
        {
            PARAGRAPH_LOG("Failed to initialize words vector");
            return false;
        }
    }
    return true;
}
