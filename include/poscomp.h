#pragma once
#include "basecomp.h"
#include "typedefs.h"

struct Positional: public BaseComponent {

    uint pos[2]; // x, y
    uint codepoint; // display character

    Positional(void);
    Positional(uint x, uint y);
    uint x(void);
    uint y(void);
};
