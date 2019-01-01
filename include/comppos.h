#pragma once
#include "compbase.h"
#include "comptags.h"
#include "typedefs.h"
#include "BearLibTerminal.h"

struct Positional: public BaseComponent {

    uint pos[2]; // x, y
    uint codepoint; // display character

    Positional(void);
    Positional(uint x, uint y, uint codepoint);
    ~Positional(void);

    uint x(void) const;
    uint y(void) const;
};
