#pragma once

// A class to represent a menu overlaid over main UI content

// Standard header file imports
#include <memory>
#include <vector>

// Custom class header file imports
#include "Rect.h"
#include "UIElement.h"

// Forward declarations
class Button;
class Font;
class GameState;
class Paragraph;
class Renderer;
struct SDL_Renderer;
class Text;

// Primary class declaration
class OverlayMenu : public UIElement
{
private:
    // Variables
    Rect bg;
    std::vector<std::shared_ptr<Paragraph>> paras;
    std::unique_ptr<Text> title;
    std::unique_ptr<Button> xBtn;

    // Methods
    bool makePara(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
                  std::string);
    bool makeParas(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
                   std::vector<std::string>&);
    bool makeTitle(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
                   std::string);
    void makeXBtn(std::shared_ptr<Renderer>, std::shared_ptr<Font>);
    void render(void);
    void render(GameState&);

public:
    // Methods
    OverlayMenu(std::shared_ptr<Renderer>, std::shared_ptr<Font>,
                std::vector<std::string>&, SDL_Rect pos);
    ~OverlayMenu(void);
    void handleMouseEvent(GameState&, SDL_Event&, SDL_Point);
};
