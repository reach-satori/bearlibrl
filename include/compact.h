#pragma once
#include "compbase.h"
#include "comptags.h"
#include "entity.h"
#include "events.h"
#include "menus.h"

struct Actional: public BaseComponent {
    uint base_speed;
    uint speed;
    int tick;

    Actional(int spd, COMPONENT_TAG tag);
    virtual void take_action(void) = 0;
};

///////////

struct PlayerActional: public Actional {
    std::shared_ptr<Entity> target;

    PlayerActional(int spd);
    void check_next_action(void);
    void take_action(void);
};

///////////

struct EmptyActional : public Actional {
    EmptyActional(int spd);
    void take_action(void);
};

Positional* get_target();


