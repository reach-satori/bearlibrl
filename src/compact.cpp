#include "compact.h"
#include "globals.h"

Actional::Actional(int spd, COMPONENT_TAG tag) : BaseComponent(tag), base_speed(spd), speed(spd), tick(spd) {}

//////////
//////////

PlayerActional::PlayerActional(int spd) : Actional(spd, C_ACT_PLAYER) {}

void PlayerActional::take_action(void) {

    auto pos = parent.lock()->get_component<Positional>(C_POSITIONAL);

    uint x = pos->pos[0];
    uint y = pos->pos[1];
    switch(key) {
        case TK_UP    :
            pos->move(x, y-1);
            break;
        case TK_DOWN    :
            pos->move(x, y+1);
            break;
        case TK_LEFT    :
            pos->move(x-1, y);
            break;
        case TK_RIGHT    :
            pos->move(x+1, y);
            break;
    }

    key = 0;

}

//////////
//////////


EmptyActional::EmptyActional(int spd) : Actional(spd, C_ACT_EMPTY) {}

void EmptyActional::take_action(void) {
    printf("empty action taken\n");
}



