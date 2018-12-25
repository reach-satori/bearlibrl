#include "BearLibTerminal.h"
#include <stdio.h>
#include <set>


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

    std::set<std::shared_ptr<Entity>> entities = std::set<std::shared_ptr<Entity>>();
    auto player = std::make_shared<Entity>();
    auto pos = std::make_shared<Positional>(13, 13);
    pos->codepoint = 0x40;
    player->add_component(std::move(pos));

    entities.insert(player);



    //main loop
    while (key != TK_CLOSE) {

        draw_map(map);
        draw_entities(entities);


        terminal_refresh();
        terminal_clear();
        terminal_delay(20);
    }

    terminal_close();
}
