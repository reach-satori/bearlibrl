#include "compact.h"
#include "globals.h"

static void player_attack(int x, int y) {
    printf("reached player attack \n");
    auto& currlvl = levelmanager->get_change_currlvl();
    auto ppos = player->get_component<Positional>(C_POSITIONAL);
    std::vector<Vital*> vit = currlvl.get_components_in_spot<Vital>(ppos->f(), x, y, C_VITAL);
    assert(vit.size() < 2);
    if (vit.empty()) {
        You("swing uselessly at the air.");
        return;
    } else {
        common_attack(player.get(), vit[0]->parent.lock().get());
    }
}

static void player_drop_item() {
    std::shared_ptr<Entity> item = retrieve_chosen_item();
    auto inv = player->get_component<Inventorial>(C_INV);
    int status = inv->remove_from_inventory(item);
    switch(status) {
        case 0:
            You(txt("dropped a %s.", item->name.c_str()).c_str());
            break;
        case -5:
            break;
        default:
            tolog("Could not drop that item.");
            break;
    }
}

static void player_pickup_confirm() {
    std::shared_ptr<Entity> item = retrieve_chosen_item();
    auto status = item_pickup(player.get(), item);
    switch (status) {
        case 0:
            You(txt("picked up a %s.", item->name.c_str()).c_str());
            break;
        case -2:
            tolog("That's too heavy to pick up.");
            break;
        case -5:
            break;
        default:
            You("can't pick that up.");
            break;
    }
};

static void player_move(int x, int y) {
    auto ppos = player->get_component<Positional>(C_POSITIONAL);
    move(player.get(),ppos->f(), x, y);
};

static void player_zmove(int dir) {
    auto ppos = player->get_component<Positional>(C_POSITIONAL);
    auto pfloor = ppos->f();
    auto lvl = levelmanager->get_change_currlvl();
    auto tile = lvl.at(pfloor, ppos->x(), ppos->y());

    if (tile->tag != T_RAMP) {
        tolog("No ramps to climb here.");
        return;
    } else if
    (pfloor + dir >= lvl.depth ||
     pfloor + dir < 0 ||
     lvl.at(pfloor + dir, ppos->x(), ppos->y())->tag != T_RAMP) {
        tolog("You can't do that.");
        return;
    }

    move(player.get(),ppos->f() + dir, ppos->x(), ppos->y());
};

static void player_inventory_open() {
    //walking through the tree to get the player inventory items
    Inventorial const * inv = player->get_component<Inventorial const>(C_INV);
    item_menu_update(inv->inventory, inv->maxweight, inv->currload);
};

static void player_pickup_open() {
    Positional const * ppos = player->get_component<Positional const>(C_POSITIONAL);
    auto icarr = levelmanager->get_const_currlvl().get_components_in_spot<Carrial>(ppos->f(), ppos->x(), ppos->y(), C_CARR);

    if (icarr.empty()) { // no item on the ground
        tolog("Nothing to pick up here.");
        input.domainstack.pop();

    }
    /**else if (icarr.size() == 1) { //shortcut the pickup menu if there's only one item to get
     * currently commented out because this function is only entered if game_running is false, allowing
     * the player to pick up an item at no turn cost...
        auto ent = icarr[0]->parent.lock()->get_shared();
        int status = item_pickup(player.get(), ent);
        switch (status) {
            case 0:
                You(txt("picked up a %s.", ent->name.c_str()).c_str());
                break;
            case -2:
                tolog("That's too heavy to pick up.");
                break;
            default:
                You("can't pick that up.");
                break;
        }
        input.domainstack.pop();
    }**/
    else { // initialize the menu for pick up of multiple items
        auto items = levelmanager->get_const_currlvl().get_components_in_spot<Carrial>(ppos->f(), ppos->x(), ppos->y(), C_CARR);
        std::set<std::shared_ptr<Entity>> out;
        for (auto& it : items) {
            if (it->parent.lock()->get_component<Positional>(C_POSITIONAL) != nullptr)
                out.insert(it->parent.lock());
        }
        auto inv = player->get_component<Inventorial>(C_INV);
        item_menu_update(out, inv->maxweight, inv->currload);
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
        Positional * pos = ent->get_component<Positional>(C_POSITIONAL);

        uint x = pos->x();
        uint y = pos->y();
        //big switch
        input.last_key = 0;
        input.game_running = false;
        switch( input.last_cmd ) {
            case INVENTORY_DROP:
                player_drop_item();
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
            case MOVE_UP    :
                player_zmove(1);
                break;
            case MOVE_DOWN    :
                player_zmove(-1);
                break;
            case ATK_N    :
                player_attack( x, y-1);
                break;
            case ATK_S    :
                player_attack( x, y+1);
                break;
            case ATK_W    :
                player_attack( x-1, y);
                break;
            case ATK_E    :
                player_attack( x+1, y);
                break;
            case ATK_NE    :
                player_attack( x+1, y-1);
                break;
            case ATK_NW    :
                player_attack( x-1, y-1);
                break;
            case ATK_SW    :
                player_attack( x-1, y+1);
                break;
            case ATK_SE    :
                player_attack( x+1, y+1);
                pos->setpos(1, x, y);
                printf("%d\n", pos->f());
                break;
            case PICKUP_CONFIRM:
                player_pickup_confirm();
                break;
            case NONE      :
                printf("NONE in player\n");
                break;
            default:
                printf("reaching this spot means a command that should not have moved game time has\n");
        }

    } else {
        switch (input.last_cmd) {
                //nothing here actually triggers a menu open: they just initialize the necessary data in menus.cpp
                //the thing that decides what menu gets shown is the command domain in input
            case MENU_CANCEL:
                break;
            case PICKUP_OPEN:
                player_pickup_open();
                break;
            case INVENTORY_OPEN:
                player_inventory_open();
                break;
            case MENU_UP:
                menu_scroll(-1);
                break;
            case MENU_DOWN:
                menu_scroll(1);
                break;
            case COMMON_ACTION_OPEN:
                break;
            case NONE:
                break;
            default:
                printf("reaching this spot means a command that should have moved game time has not\n");
        }
    }
}

//////////
//////////

EmptyActional::EmptyActional(int spd) : Actional(spd, C_ACT_EMPTY) {}

void EmptyActional::take_action(void) {
    printf("empty action taken\n");
}



