#pragma once

// A class to represent a paragraph of continuous text

// Standard header file imports
#include <memory>
#include <string>
#include <vector>

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class Font;
class GameState;
class Text;

// Primary class declaration
class Paragraph : public UIElement
{
private:
    // Variables
    std::string str;
    std::vector<std::shared_ptr<Text>> words;
    // Methods
    bool calculateWordY(int, int);
    bool calculateWordsY(int);
    void render(void);
    void render(GameState&);
    std::unique_ptr<Text> str2Txt(std::shared_ptr<Renderer>,
                                  std::shared_ptr<Font>, SDL_Color,
                                  std::string);
    bool wordInit(std::shared_ptr<Renderer>, std::shared_ptr<Font>, SDL_Color,
                  std::string);
    bool wordsInit(std::shared_ptr<Renderer>, std::shared_ptr<Font>, SDL_Color);

public:
    // Methods
    Paragraph(std::shared_ptr<Renderer>, std::shared_ptr<Font>, SDL_Color,
              std::string, unsigned int, unsigned int, unsigned int);
    ~Paragraph();
    bool setY(int);
};
