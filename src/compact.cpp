#include "compact.h"
#include "globals.h"

static void player_move(int x, int y) {
    move(player.get(), x, y);
};

static void player_pickup_open() {
    Positional const * ppos = player->get_component<Positional const>(C_POSITIONAL);
    std::vector<Carrial const *> items = levelmanager->get_const_currlvl().get_components_in_spot<Carrial const>(ppos->x(), ppos->y(), C_CARR);

    if (items.empty()) { // no item on the ground
        tolog("Nothing to pick up there.");
        input.domainstack.pop();

    } else if (items.size() == 1) { //shortcut the pickup menu if there's only one item to get
        auto topickup = items[0]->parent.lock();
        int status = item_pickup(player.get(), topickup);
        switch (status) {
            case 0:
                You("picked up a thing.");
            case -2:
                tolog("That's too heavy to pick up.");
            default:
                You("can't pick that up.");
        }
        input.domainstack.pop();

    } else { // initialize the menu for pick up of multiple items
        auto const inv = player->get_component<Inventorial const>(C_INV);
        item_menu_update(items, inv->maxweight, inv->currload);
    }

};

/////////////////////
//////////////////////

Actional::Actional(int spd, COMPONENT_TAG tag) : BaseComponent(tag), base_speed(spd), speed(spd), tick(spd) {}


////////////////
////////////////

PlayerActional::PlayerActional(int spd) : Actional(spd, C_ACT_PLAYER) {}

void PlayerActional::take_action(void) {
    if (input.game_running) {
        Entity *ent = parent.lock().get();
        Positional const * pos = ent->get_component<Positional const>(C_POSITIONAL);

        uint x = pos->x();
        uint y = pos->y();
        //big switch
        input.last_key = 0;
        input.game_running = false;
        switch( input.last_cmd ) {
            case NONE      :
                printf("NONE in player\n");
                break;
            case MOVE_N    :
                player_move( x, y-1);
                break;
            case MOVE_S    :
                player_move( x, y+1);
                break;
            case MOVE_W    :
                player_move( x-1, y);
                break;
            case MOVE_E    :
                player_move( x+1, y);
                break;
            case MOVE_NE    :
                player_move( x+1, y-1);
                break;
            case MOVE_NW    :
                player_move( x-1, y-1);
                break;
            case MOVE_SW    :
                player_move( x-1, y+1);
                break;
            case MOVE_SE    :
                player_move( x+1, y+1);
                break;
            default:
                printf("DEFAULT CASE REACHED IN PLAYER TAKE_ACTION\n");
        }

    } else {
        switch (input.last_cmd) {
            case MENU_CANCEL:
                tolog("menu cancel");
                break;
            case PICKUP_OPEN:
                player_pickup_open();
                break;
            case NONE:
                break;
        }
    }
}

//////////
//////////

EmptyActional::EmptyActional(int spd) : Actional(spd, C_ACT_EMPTY) {}

void EmptyActional::take_action(void) {
    printf("empty action taken\n");
}



