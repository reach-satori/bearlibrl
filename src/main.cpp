#include <stdio.h>
#include <set>
#include "BearLibTerminal.h"

#include "typedefs.h"
#include "tile.h"
#include "map.h"
#include "entity.h"
#include "poscomp.h"
#include "comptags.h"
#include "draw.h"

#include "globals.h"


int main()
{
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
    player->add_component(pos);

    cent->insert(player);

    //main loop
    while (key != TK_CLOSE) {

        //input
        while (terminal_has_input()) {
            key = terminal_read();
        }
        uint& x = pos->pos[0];
        uint& y = pos->pos[1];
        switch(key) {
            case TK_UP    :
                if (cmap->is_passable(x, y-1)) {
                    pos->pos[1] -= 1;
                }
                break;
            case TK_DOWN    :
                if (cmap->is_passable(x, y+1)) {
                    pos->pos[1] += 1;
                }
                break;
            case TK_LEFT    :
                if (cmap->is_passable(x-1, y)) {
                    pos->pos[0] -= 1;
                }
                break;
            case TK_RIGHT    :
                if (cmap->is_passable(x+1, y)) {
                    pos->pos[0] += 1;
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
