#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>
#include "BearLibTerminal.h"

#include "typedefs.h"
#include "tile.h"
#include "map.h"

#include "entity.h"
#include "poscomp.h"
#include "actcomp.h"
#include "comptags.h"

#include "draw.h"
#include "input.h"

#include "globals.h"

#define FRAMEWAIT 60

void player_act() {

}

void tick_game() {
    //first pass to order speeds
    auto pact = player->get_action();

    while(pact->tick > 0) {

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
                printf("action from other entity happened\n#####\n");
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
    terminal_open();
    terminal_set("input.events=keypress");

    terminal_refresh();

    //map creation
    Map map(80, 25);
    create_room(&map, 10, 10, 10, 10);
    cmap = std::make_shared<Map>(map);

    //initializing entities here for now
    std::set<std::shared_ptr<Entity>> entities = std::set<std::shared_ptr<Entity>>();
    player->add_component(std::make_shared<Positional>(13, 13, 0xBF));
    player->add_component(std::make_shared<Action>(1000));

    auto other_entity = std::make_shared<Entity>();
    other_entity->add_component(std::make_shared<Positional>(13, 13, 0x21));
    other_entity->add_component(std::make_shared<Action>(300));

    cent->insert(player);
    cent->insert(other_entity);

    //main loop
    int key=0;
    while (key != TK_CLOSE) {

        if (game_running) {
            tick_game(); // deals with entities that have an action component
        }

        game_running = false;
        while (terminal_has_input()) {
            key = terminal_read(); // get our input in non-blocking way
            game_running = true;
        }
        process_input(key);
        key=0;

        draw_map(cmap);
        draw_entities(cent);

        terminal_refresh();
        terminal_clear();
        terminal_delay(1000/FRAMEWAIT);
    }

    terminal_close();
}
