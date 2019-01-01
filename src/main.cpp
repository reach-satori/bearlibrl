#include <stdio.h>
#include <algorithm>
#include <set>
#include <cassert>

#include "BearLibTerminal.h"

/////////////////////

#include "typedefs.h"

// entity
#include "entity.h"
#include "init_entity.h"

// components
#include "compcarr.h"
#include "compinv.h"
#include "comppos.h"
#include "compact.h"
#include "comphp.h"

// stuff
#include "tile.h"
#include "level.h"
#include "camera.h"
#include "menus.h"
#include "globals.h"
#include "consts.h"


void tick_game() {
    auto pact = player->get_component<Actional>(C_ACT);

    //we want shared pointer copies here: it guarantees entities are not
    //destroyed until the end of tick_game, and no dangling pointers get accessed
    auto entset = levelmanager->get_current_entities();
    while(true) {

        auto acts = levelmanager->get_current_components<Actional>(C_ACT);

        //get lowest tick (action that comes soonest)
        int lowest_tick = 1000;
        for (const auto& act: acts) {
            lowest_tick = act->tick < lowest_tick ? act->tick : lowest_tick;
        }

        //player should be last
        acts.erase(std::remove(acts.begin(), acts.end(), pact), acts.end());
        acts.push_back(pact);

        //every entity with an action component takes their action, from fastest to slowest
        for (auto act: acts) {
            act->tick -= lowest_tick;
            if (act->tick <= 0){
                act->take_action();
                act->tick += act->speed;
                if (act == pact) goto turn_end;
            }
        }
    }
    turn_end:
    ;
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

    //levelmanager initiation initiates a level
    //map creation (idk where to move this)
    auto& cmap = levelmanager->get_change_currlvl();
    cmap.create_room(  1, 1, 78, 10);
    cmap.create_room(50, 1, 6, 22);
    cmap.randomize();

    //initializing entities here for now
    init_entity(E_TEST)->get_component<Positional>(C_POSITIONAL)->setpos(5, 5);
    auto it = init_entity(E_TEST);
    it->get_component<Positional>(C_POSITIONAL)->setpos(5, 5);
    it->name = "Test object 2";

    levelmanager->add_entity_to_currlvl(player);
    player->add_component(std::make_unique<Positional>(30, 10,0x40));
    player->add_component(std::make_unique<PlayerActional>(1000));
    auto inv = std::make_unique<Inventorial>();
    player->add_component(std::move(inv));

    //main loop
    while (input.last_key != TK_CLOSE) {

        while (terminal_has_input()) {
            input.read_key();
        }

        //stuff that should happen once per "turn"(player action)
        if (input.game_running) {
            tick_game(); //deals with entities that have an action component
            Positional const * pos = player->get_component<Positional const>(C_POSITIONAL);
            camera.center_on_player();

            //fov
            levelmanager->get_change_currlvl().all_nonvisible();
            levelmanager->get_change_currlvl().do_fov(pos->x(), pos->y(), 60);
        } else {
            //this is a little ugly but i want every command in one place (inside player action component)
            player->get_component<Actional>(C_ACT)->take_action();
        }

        camera.draw_world();
        camera.draw_entities();
        draw_menus();

        terminal_refresh();
        terminal_clear();
        /* terminal_delay(1000/FRAMEWAIT); */
        //not sure if i need this
        input.last_cmd = NONE;
    }

    terminal_close();
}
