#pragma once
#include "basecomp.h"
#include "typedefs.h"

struct Positional: public BaseComponent {

    uint pos[2]; // x, y
    uint codepoint; // display character

    Positional(void);
    Positional(uint x, uint y);
    ~Positional(void);

    uint x(void);
    uint y(void);
    void move(uint x, uint y);
};
