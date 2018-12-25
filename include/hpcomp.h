#pragma once
#include "basecomp.h"
#include "comptags.h"
#include "typedefs.h"

struct Vital: public BaseComponent {
    uint maxhp;
    int currhp;
    //death function;??

    Vital(void);
    Vital(uint maxhp);
    ~Vital(void);
};
