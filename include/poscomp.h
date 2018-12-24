#pragma once
#include "basecomp.h"

struct Positional: public BaseComponent {

    unsigned int pos[2]; // x, y

    Positional(void);
    Positional(unsigned int x, unsigned int y);
    unsigned int x(void);
    unsigned int y(void);
};
