#pragma once
#include "basecomp.h"
#include "typedefs.h"
#include "comptags.h"

struct Actional: public BaseComponent {
    int base_speed;
    int speed;
    int tick;

    Actional(int spd);
    Actional();
};
