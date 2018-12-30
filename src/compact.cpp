#include "compact.h"
#include "globals.h"

Actional::Actional(int spd, COMPONENT_TAG tag) : BaseComponent(tag), base_speed(spd), speed(spd), tick(spd) {}

////////////////
////////////////

PlayerActional::PlayerActional(int spd) : Actional(spd, C_ACT_PLAYER) {}

void PlayerActional::take_action(void) {
    if (input.game_running) {
        Entity *ent = parent.lock().get();
        Positional const * pos = ent->get_component<Positional const>(C_POSITIONAL);

        uint x = pos->pos[0];
        uint y = pos->pos[1];
        //big switch
        input.last_key = 0;
        input.game_running = false;
        switch( input.last_cmd ) {
            case NONE      :
                printf("NONE in player\n");
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
            default:
                printf("DEFAULT CASE REACHED IN PLAYER TAKE_ACTION\n");
        }

    } else {
        switch (input.last_cmd) {
            case TEST:
                printf("test success\n");
                break;
            case EXIT_MENU:
                printf("exit menu\n");
                break;
            default:
                ;
        }
    }
    //not sure if i need this
    input.last_cmd = NONE;
}

//////////
//////////

EmptyActional::EmptyActional(int spd) : Actional(spd, C_ACT_EMPTY) {}

void EmptyActional::take_action(void) {
    printf("empty action taken\n");
}



