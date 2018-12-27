#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>
#include "BearLibTerminal.h"

#include "typedefs.h"

#include "tile.h"
#include "level.h"

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


void tick_game() {
    Actional *pact = dynamic_cast<Actional*>(player->search_tags_for(C_ACT));
    while(pact->tick > 0) {

        //get lowest tick (action that comes soonest)
        int lowest_tick = 1000;
        for (auto ent: *cent) {
            Actional *act = dynamic_cast<Actional*>(ent->search_tags_for(C_ACT));
            if (act == nullptr)
                continue;
            lowest_tick = act->tick < lowest_tick ? act->tick : lowest_tick;
        }

        //every entity with an action component takes their action, from fastest to slowest
        for (auto ent: *cent) {
            Actional *act = dynamic_cast<Actional*>(ent->search_tags_for(C_ACT));
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
    cmap = std::make_shared<Level>(200, 200);
    cmap->create_room(  1, 1, 100, 10);
    cmap->create_room(50, 1, 6, 150);


    //initializing entities here for now
    auto other_entity = std::make_shared<Entity>();
    cent->insert(other_entity);
    other_entity->add_component(std::make_unique<Positional>(13, 5, 0x21));
    other_entity->add_component(std::make_unique<Actional>(500));
    other_entity->add_component(std::make_unique<Carrial>());

    auto item2 = std::make_shared<Entity>();
    cent->insert(item2);
    item2->add_component(std::make_unique<Positional>(13, 5, 0x21));
    item2->add_component(std::make_unique<Actional>(500));
    item2->add_component(std::make_unique<Carrial>());

    //pointer to player is a global
    player->add_component(std::make_unique<Positional>(5, 5,0x40));
    player->add_component(std::make_unique<Actional>(1000));
    auto inv = std::make_unique<Inventorial>();
    cent->insert(player);
    player->add_component(std::move(inv));




    //main loop
    int key=0;
    while (key != TK_CLOSE) {

        if (game_running) {
            tick_game(); // deals with entities that have an action component
            camera->center(dynamic_cast<Positional*>(player->search_tags_for(C_POSITIONAL)));
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
