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
    COMMAND_TAG cmd = input.get_next_cmd();

    //big switch
    switch(cmd) {
        case NONE      :
            break;
        case MOVE_N    :
            move(ent, x, y-1);
            break;
        case MOVE_S    :
            move(ent, x, y+1);
            break;
        case MOVE_W    :
            move(ent, x-1, y);
            break;
        case MOVE_E    :
            move(ent, x+1, y);
            break;
        case MOVE_NE    :
            move(ent, x+1, y-1);
            break;
        case MOVE_NW    :
            move(ent, x-1, y-1);
            break;
        case MOVE_SW    :
            move(ent, x-1, y+1);
            break;
        case MOVE_SE    :
            move(ent, x+1, y+1);
            break;
        case PICKUP_OPEN :
            auto ents = levelmanager->get_const_currlvl().get_entities_in_spot(x, y);
            for( auto it = ents.begin(); it != ents.end(); it++){
                item_pickup(ent, *it);
            }
            break;

    }


}

//////////
//////////


EmptyActional::EmptyActional(int spd) : Actional(spd, C_ACT_EMPTY) {}

void EmptyActional::take_action(void) {
}



