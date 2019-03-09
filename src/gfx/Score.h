#pragma once

// A class to represent a player score

// Standard header file imports
#include <memory>
#include <string>

// Custom class header file imports
#include "UIElement.h"

// Forward declarations
class Font;
class GameState;
class Renderer;
class Text;

// Primary class declaration
class Score : public UIElement
{
private:
    // Variables
    int cachedScore;
    std::weak_ptr<Font> font;
    std::unique_ptr<Text> scoreHeader;
    std::unique_ptr<Text> scoreVal;
    // Methods
    bool makeScoreVal(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
                      int val);
    void render(void);
    void render(GameState&);

public:
    // Methods
    Score(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
          std::string, int, unsigned int, unsigned int);
    ~Score(void);
    int getMaxTextH(void);
    int getNum(void);
    bool toZero(void);
    bool update(int);
};
