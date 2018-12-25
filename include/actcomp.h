
#pragma once
#include "basecomp.h"
#include "typedefs.h"

struct Action: public BaseComponent {
    const int base_speed;
    int speed;
    int tick;

    Action(int spd);
    Action();
};
