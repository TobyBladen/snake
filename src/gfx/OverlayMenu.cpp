// A file to implement OverlayMenu class methods

// Standard header file imports
#include <SDL2/SDL.h>
#include <string>

// Custom class header file imports
#include "Button.h"
#include "GameState.h"
#include "OverlayMenu.h"
#include "Paragraph.h"
#include "Renderer.h"
#include "Text.h"

// Import stylesheet
#include "stylesheet.h"

// Define macro debug log functionality
#include "gfx_log.h"
#if defined(DEBUG_ALL) || defined(DEBUG_OVERLAY_MENU)
#include <iostream>
#define OM_LOG(a) std::cout << "Overlay menu log: " << a << std::endl
#else
#define OM_LOG(a)
#endif

// Public method definitions

// Create a new overlay menu with specified text content and dimensions
OverlayMenu::OverlayMenu(std::shared_ptr<Renderer> rnd,
                         std::shared_ptr<Font> fnt,
                         std::vector<std::string>& txtCt, SDL_Rect pos) :
UIElement(rnd, pos),
bg(rnd, pos, BG_COLOR),
xBtn(nullptr)
{
    std::string e = "Initialization error - ";
    if(rnd == nullptr) OM_LOG(e + "renderer is null");
    else if(fnt == nullptr) OM_LOG(e + "font is null");
    else
    {
        makeXBtn(rnd, fnt);
        int sz = txtCt.size();
        if(sz > 0 && !makeTitle(rnd, fnt, txtCt[0]))
        {
            OM_LOG(e + "failed to make title");
        }
        if(sz > 1 && !makeParas(rnd, fnt, txtCt))
        {
            OM_LOG(e + "failed to make paragraphs");
        }
    }
    OM_LOG("Overlay menu created");
}

OverlayMenu::~OverlayMenu(void)
{
    OM_LOG("Overlay menu destroyed");
}

// Handle mouse action in the overlay menu area
void OverlayMenu::handleMouseEvent(GameState& gs, SDL_Event& e, SDL_Point mouse)
{
    if(hidden() && e.type != SDL_MOUSEBUTTONUP)
    {
        OM_LOG(std::string("Unexpected call to handleMouseEvent ") +
                         "overlay menu is hidden.");
    }
    else if(xBtn->overlaps(mouse))
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            xBtn->click(gs);
        }
        else
        {
            xBtn->mouseOver();
        }
    }
    else
    {
        xBtn->mouseOut();
    }
}

// Private method definitions

// Make a new paragraph with specified content and add it to the vector
bool OverlayMenu::makePara(std::shared_ptr<Renderer> rnd,
                           std::shared_ptr<Font> fnt,
                           std::string str)
{
    int yPos;
    if(paras.empty()) yPos = title->getY() + title->getH() + TITLE_MARGIN;
    else
    {
        auto last = paras.back();
        if(last == nullptr)
        {
            OM_LOG("Failed to get para y position - previous para was null");
            return false;
        }
        yPos = last->getY() + last->getH() + LINE_GAP;
    }
    SDL_Color col = TEXT_COLOR;
    auto para = std::make_shared<Paragraph>(rnd, fnt, col, str,
                                            MENU_MARGIN, yPos,
                                            pos.w - (MENU_MARGIN * 2));
    paras.push_back(para);
    return true;
}

// Make a collection of paragraphs from a vector of strings
bool OverlayMenu::makeParas(std::shared_ptr<Renderer> rnd,
                           std::shared_ptr<Font> fnt,
                           std::vector<std::string>& txtCt)
{
    int sz = txtCt.size();
    for(int i = 1; i < sz; i++)
    {
        std::string paraStr = txtCt[i];
        if(paraStr == "") OM_LOG("Warning - null paragraph detected");
        else if(!makePara(rnd, fnt, paraStr))
        {
            OM_LOG(std::string("Failed to make paras - string at index ") +
                   std::to_string(i) + " caused an issue");
            return false;
        }
    }
    return true;
}

// Make a 'title' text object from specified string
bool OverlayMenu::makeTitle(std::shared_ptr<Renderer> rnd,
                           std::shared_ptr<Font> fnt, std::string str)
{
    SDL_Color col = TEXT_COLOR;
    int titleY = xBtn->getY() + xBtn->getH() + MENU_MARGIN;
    title = std::make_unique<Text>(rnd, fnt, col, str, TBD, titleY);
    int titleX = (pos.w - title->getW())/2;
    if(!title->setX(titleX))
    {
        OM_LOG("Failed to make title - text centering failed");
        title.reset(nullptr);
        return false;
    }
    return true;
}

// Make an 'exit' button
void OverlayMenu::makeXBtn(std::shared_ptr<Renderer> rnd,
                           std::shared_ptr<Font> fnt)
{
    SDL_Rect dm = { pos.w - X_BUTTON_WIDTH - MENU_MARGIN,
                    MENU_MARGIN,
                    X_BUTTON_WIDTH,
                    BUTTON_HEIGHT };
    SDL_Color col = BUTTON_COLOR;
    SDL_Color hvCol = BUTTON_HOVER_COLOR;
    auto func = [](GameState& g) { g.resume(); };
    xBtn = std::make_unique<Button>(rnd, fnt, dm, col, hvCol, "X", func);
}

// Render all menu content to the game window
void OverlayMenu::render(void)
{
    std::shared_ptr<Renderer> lRend = rend.lock();
    if(lRend == nullptr)
    {
        OM_LOG("Could not render - Renderer was already destroyed");
    }
    else
    {
        SDL_RenderSetViewport(lRend->getRaw(), &pos);
        bg.show();
        if(xBtn) xBtn->show();
        if(title) title->show();
        for(auto para : paras)
        {
            if(para) para->show();
        }
    }
}

// Render all menu content to the game window
void OverlayMenu::render(GameState& gs)
{
    OM_LOG("Warning: game state arg will be ignored in rendering");
    (void)(gs);
    render();
}
