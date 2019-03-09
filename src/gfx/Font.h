#pragma once

// A class to wrap raw pointer to TTF_Font object

// Standard header file imports
#include <string>

// Forward declarations
typedef struct _TTF_Font TTF_Font;

// Primary class declaration
class Font
{
private:
    // Variables
    TTF_Font* f;

public:
    // Methods
    Font(std::string, unsigned int);
    ~Font(void);
    TTF_Font* getRaw(void);
};
