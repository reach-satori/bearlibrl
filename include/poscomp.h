#pragma once
#include "basecomp.h"

struct Positional: public BaseComponent {

    int pos[2]; // x, y

    public:
        Positional();
        unsigned int x(void);
        unsigned int y(void);
};
