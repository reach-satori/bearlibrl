#include "compact.h"
#include "globals.h"

Actional::Actional(int spd, COMPONENT_TAG tag) : BaseComponent(tag), base_speed(spd), speed(spd), tick(spd) {}

//////////
//////////

PlayerActional::PlayerActional(int spd) : Actional(spd, C_ACT_PLAYER) {}

void PlayerActional::take_action(void) {

    Entity *ent = parent.lock().get();
    Positional* const pos = ent->get_component<Positional>(C_POSITIONAL);

    uint x = pos->pos[0];
    uint y = pos->pos[1];
    switch(key) {
        case TK_UP    :
            move(ent, x, y-1);
            break;
        case TK_DOWN    :
            move(ent, x, y+1);
            break;
        case TK_LEFT    :
            move(ent, x-1, y);
            break;
        case TK_RIGHT    :
            move(ent, x+1, y);
            break;
        case TK_G :
            auto ents = levelmanager->get_const_currlvl()->get_entities_in_spot(x, y);
            for( auto it = ents.begin(); it != ents.end(); it++){
                item_pickup(ent, *it);
            }
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



