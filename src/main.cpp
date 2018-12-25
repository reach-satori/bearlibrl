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

#include "globals.h"

void player_act() {

}

void tick_game() {

    //first pass to order speeds
    auto pact = player->get_action();
    std::vector<std::shared_ptr<Action>> acts;
    std::vector<int> speeds;
    for (auto const& ent: *cent) {
        auto act = ent->get_action();
        if (act == nullptr)
            continue;
        acts.push_back(act);
        speeds.push_back(act->speed);
    }

    std::sort(speeds.begin(), speeds.end());
    assert(speeds.size() == acts.size());

    int loopnum = 0;
    while(pact->tick > 0) {
        //every entity with an action component takes their action
        int tickdec = speeds[loopnum];
        for (auto act: acts) {
            act->tick -= tickdec;
            if (act.get() != pact.get() && act->tick <= 0 ) {
                act->tick += act->speed;
                //do action with AI here
            }
            if (pact->tick <= 0)
                break;
        }
        loopnum++;
    }
    pact->tick += pact->speed;
    printf("%i\n", pact->tick);
    /* player_act(); */
}

int main() {
    terminal_open();
    terminal_set("input.events=keypress");

    terminal_refresh();
    int key=0;

    //map creation
    Map map(80, 25);
    create_room(&map, 10, 10, 10, 10);
    cmap = std::make_shared<Map>(map);

    //initializing entities here for now
    std::set<std::shared_ptr<Entity>> entities = std::set<std::shared_ptr<Entity>>();
    auto pos = std::make_shared<Positional>(13, 13);
    pos->codepoint = 0x40;
    player->add_component(std::move(pos));
    player->add_component(std::make_shared<Action>(1000));

    cent->insert(player);

    //main loop
    while (key != TK_CLOSE) {

        tick_game();
        while (terminal_has_input()) {
            key = terminal_read();
        }
        uint* pos = player->get_pos();

        assert(pos != nullptr);

        uint& x = pos[0];
        uint& y = pos[1];
        switch(key) {
            case TK_UP    :
                if (cmap->is_passable(x, y-1)) {
                    y -= 1;
                }
                break;
            case TK_DOWN    :
                if (cmap->is_passable(x, y+1)) {
                    y += 1;
                }
                break;
            case TK_LEFT    :
                if (cmap->is_passable(x-1, y)) {
                    x -= 1;
                }
                break;
            case TK_RIGHT    :
                if (cmap->is_passable(x+1, y)) {
                    x += 1;
                }
                break;
        }
        key = 0;

        draw_map(cmap);
        draw_entities(cent);

        terminal_refresh();
        terminal_clear();
        terminal_delay(20);
    }

    terminal_close();
}
