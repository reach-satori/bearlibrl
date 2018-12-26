#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>
#include "BearLibTerminal.h"

#include "typedefs.h"

#include "tile.h"
#include "map.h"

#include "entity.h"
#include "compcarr.h"
#include "compinv.h"
#include "comppos.h"
#include "compact.h"
#include "comphp.h"

#include "input.h"
#include "camera.h"
#include "menus.h"
#include "globals.h"
#include "consts.h"

#define FRAMEWAIT 60

void tick_game() {
    auto pact = player->get_action();
    while(pact->tick > 0) {

        //get lowest tick (action that comes soonest)
        int lowest_tick = 1000;
        for (auto ent: *cent) {
            auto act = ent->get_action();
            if (act == nullptr)
                continue;
            lowest_tick = act->tick < lowest_tick ? act->tick : lowest_tick;
        }

        //every entity with an action component takes their action, from fastest to slowest
        for (auto ent: *cent) {
            auto act = ent->get_action();
            if (act == nullptr)
                continue;

            act->tick -= lowest_tick;
            if (act.get() != pact.get() && act->tick <= 0 ) {
                act->tick += act->speed;
                //do action with AI here
            }
            if (pact.get() == act.get() && act->tick <= 0)
                break;
        }
    }
    pact->tick += pact->speed;
    //player action comes right after this?
}

int main() {
    //init  (terminal doesn't pop up until first refresh call)
    terminal_open();
    terminal_layer(DEFAULT_LAYER);
    terminal_color(0xffffffff);
    char buffer[256];
    std::snprintf(buffer, 256, "input.events=keypress; window.size=%dx%d", CONSOLE_WIDTH, CONSOLE_HEIGHT);
    terminal_set(buffer);
    terminal_refresh();

    //map creation
    Map map(200, 200);
    create_room(&map, 1, 1, 100, 10);
    create_room(&map, 50, 1, 6, 150);
    cmap = std::make_shared<Map>(map);


    //initializing entities here for now
    //pointer to player is a global
    player->add_component(std::make_shared<Positional>(5, 5,0x40));
    player->add_component(std::make_shared<Actional>(1000));
    //another one
    auto other_entity = std::make_shared<Entity>();
    other_entity->add_component(std::make_shared<Positional>(13, 5, 0x21));
    other_entity->add_component(std::make_shared<Actional>(500));

    cent->insert(player);
    cent->insert(other_entity);

    //main loop
    int key=0;
    while (key != TK_CLOSE) {

        if (game_running) {
            tick_game(); // deals with entities that have an action component
            camera->center(player->get_positional());
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
