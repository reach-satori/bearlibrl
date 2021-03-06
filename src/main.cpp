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
                // might want to move this to inside take_action: that way things can
                // take a variable amount of "time" (ie some actions are faster than others)
                act->tick += act->speed;
                if (act == pact) goto turn_end; // goto to break out of two loops
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
    auto& cmap = levelmanager->get_currlvl();
    cmap.randomize();
    cmap.create_room(1, 5, 6, 5, 5, T_AIR);
    *cmap.at(1, 5, 4) = Tile(T_RAMP);
    *cmap.at(2, 5, 4) = Tile(T_RAMP);
    *cmap.at(0, 5, 4) = Tile(T_RAMP);
    cmap.do_fov(0, 30, 10, 10);

    //initializing entities here for now
    init_entity(E_TEST)->get_component<Positional>(C_POSITIONAL)->setpos(1, 5, 5);
    auto it = init_entity(E_TEST);
    it->get_component<Positional>(C_POSITIONAL)->setpos(1, 5, 5);
    it->name = "Test object 2";
    it.reset();

    //camera init (using player component)
    auto ppos = std::make_unique<Positional>(1, 30, 10, 0x40);
    camera.set_pos(ppos->f(), ppos->x() - camera.width/2, ppos->y() - camera.height/2);
    auto& currlvl = levelmanager->get_currlvl();
    currlvl.do_fov(ppos->f(), ppos->x(), ppos->y(), 10);
    lvlgen(&currlvl);

    //player init
    levelmanager->add_entity_to_currlvl(player);
    player->add_component(std::move(ppos));
    player->add_component(std::make_unique<PlayerActional>(1000));
    player->add_component(std::make_unique<Offensal>(5, 5, 5, 5));
    player->add_component(std::make_unique<Statsal>(10, 10, 10, 10, 10, 10));
    player->add_component(std::make_unique<EquipInventorial>(100));

    //main loop
    while (input.last_key != TK_CLOSE) {

    Positional const * p = player->get_component<Positional const>(C_POSITIONAL);
        while (terminal_has_input()) {
            input.read_key();
        }

        //stuff that should happen once per "turn"(player action)
        if (input.game_running) {
            tick_game(); //deals with entities that have an action component

            //fov
            auto& currlvl = levelmanager->get_currlvl();
            currlvl.all_visible();
            currlvl.do_fov(p->f(), p->x(), p->y(), 10);

        } else {
            //this is a little ugly but i want every command in one place (inside player action component)
            //that includes menu control commands and others that don't advance game time
            player->get_component<Actional>(C_ACT)->take_action();
        }

        input.last_cmd = NONE;

        camera.draw_world();
        camera.draw_entities();
        draw_menus();// i think it's logical that menus aren't in the camera...

        terminal_refresh();
        terminal_clear();
        terminal_delay(1000/FRAMEWAIT);
    }

    terminal_close();
}
