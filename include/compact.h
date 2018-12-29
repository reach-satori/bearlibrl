#pragma once
#include "compbase.h"
#include "comptags.h"
#include "entity.h"

struct Actional: public BaseComponent {
    int base_speed;
    int speed;
    int tick;

    Actional(int spd, COMPONENT_TAG tag);
    virtual void take_action(void) = 0;
};

///////////

struct PlayerActional: public Actional {
    PlayerActional(int spd);
    void take_action(void);
};

///////////

struct EmptyActional : public Actional {
    EmptyActional(int spd);
    void take_action(void);
};


