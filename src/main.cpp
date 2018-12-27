#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>

#include "BearLibTerminal.h"

/////////////////////

#include "typedefs.h"

// entity
#include "entity.h"

// components
#include "compcarr.h"
#include "compinv.h"
#include "comppos.h"
#include "compact.h"
#include "comphp.h"

// stuff
#include "tile.h"
#include "level.h"
#include "input.h"
#include "camera.h"
#include "menus.h"
#include "globals.h"
#include "consts.h"


void tick_game() {
    Actional *pact = dynamic_cast<Actional*>(player->get_change_component(C_ACT));
    while(pact->tick > 0) {

        //get lowest tick (action that comes soonest)
        int lowest_tick = 1000;
        for (const auto& ent: *levelmanager->get_current_entities()) {
            Actional const *act = dynamic_cast<Actional const *>(ent->get_const_component(C_ACT));
            if (act == nullptr)
                continue;
            lowest_tick = act->tick < lowest_tick ? act->tick : lowest_tick;
        }

        //every entity with an action component takes their action, from fastest to slowest
        for (const auto& ent: *levelmanager->get_current_entities()) {
            Actional *act = dynamic_cast<Actional*>(ent->get_change_component(C_ACT));
            if (act == nullptr)
                continue;

            act->tick -= lowest_tick;
            if (act != pact && act->tick <= 0 ) {
                act->tick += act->speed;
                //do action with AI here
            }
            if (pact == act && act->tick <= 0)
                break;
        }
    }
    pact->tick += pact->speed;
    //player action comes right after this?
}

void terminal_init() {
    terminal_open();
    terminal_layer(DEFAULT_LAYER);
    terminal_color(0xffffffff);
    char buffer[256];
    std::snprintf(buffer, 256, "input.events=keypress; window.size=%dx%d", CONSOLE_WIDTH, CONSOLE_HEIGHT);
    terminal_set(buffer);
    terminal_refresh();
}

int main() {

    terminal_init();

    //levelmanager initiation initiates a
    //map creation (idk where to move this)
    auto cmap = levelmanager->get_change_currlvl();
    cmap->create_room(  1, 1, 78, 10);
    cmap->create_room(50, 1, 6, 22);
    cmap = nullptr;

    auto map2 = std::make_unique<Level>(80, 25); // currently if map size is smaller than the console size, it crashes
    map2->create_room(1, 1, 9, 9);

    //testing other stuff
    levelmanager->add_lvl(std::move(map2));
    /* levelmanager->move_to_lvl(1); */


    //initializing entities here for now
    auto item = std::make_shared<Entity>();
    levelmanager->add_entity_to_currlvl(item);
    item->add_component(std::make_unique<Positional>(13, 5, 0x21));
    item->add_component(std::make_unique<Actional>(500));
    item->add_component(std::make_unique<Carrial>());
    item.reset();

    levelmanager->add_entity_to_currlvl(player);
    player->add_component(std::make_unique<Positional>(30, 10,0x40));
    player->add_component(std::make_unique<Actional>(1000));
    auto inv = std::make_unique<Inventorial>();
    player->add_component(std::move(inv));



    //main loop
    int key=0;
    while (key != TK_CLOSE) {

        if (game_running) {
            tick_game(); // deals with entities that have an action component
            camera->center(dynamic_cast<Positional const *>(player->get_const_component(C_POSITIONAL)));
        }

        game_running = false;
        while (terminal_has_input()) {
            key = terminal_read(); // get our input in non-blocking way
            game_running = true;
        }
        process_input(key);
        key=0;

        camera->draw_world();
        camera->draw_entities();

        terminal_refresh();
        terminal_clear();
        terminal_delay(1000/FRAMEWAIT);
    }

    terminal_close();
}
