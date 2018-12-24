#include "BearLibTerminal.h"
#include <stdio.h>
#include "map.h"
#include "tile.h"
#include "entity.h"
#include "poscomp.h"
typedef unsigned int uint;

int main()
{
    terminal_open();
    terminal_set("input.events=keypress");

    int x = 10;
    int y = 10;
    terminal_put(x, y, 0x40);
    terminal_refresh();
    int key=0;

    //map creation
    WallTile wall = WallTile();
    FloorTile floor = FloorTile();
    Map map;
    map.width=80;
    map.height=25;
    std::vector<Tile*> outermost{&wall};
    std::vector<std::vector<Tile*>> col(map.height, outermost);
    map.tiles = std::vector<std::vector<std::vector<Tile*>>>(map.width, col);
    //

    //create a room in the map
    for (uint x = 10; x < 20; x++) {
        for (uint y = 10; y < 20; y++) {
            map.tiles[x][y] = std::vector<Tile*>{&floor};
        }
    }
    //

    auto player = std::make_shared<Entity>();
    auto pos = std::make_shared<Positional>(5, 5);
    player->add_component(std::move(pos));



    while (key != TK_CLOSE) {
        /* while (terminal_has_input()){ */
        /*     key = terminal_read(); */
        /* } */
        /* switch(key) { */
        /*     case TK_LEFT: x -= 1; break; */
        /*     case TK_RIGHT: x += 1; break; */
        /*     case TK_DOWN: y += 1; break; */
        /*     case TK_UP: y -= 1; break; */
        /* } */
        /* key = 0; */
        /* terminal_clear(); */
        /* terminal_put(x, y, 0x40); */
        /* terminal_refresh(); */
        //draw map
        for (int x = 0; x < map.width; x++) {
            for (int y = 0; y < map.height; y++) {
                for (auto it = map.tiles[x][y].begin(); it != map.tiles[x][y].end(); it++) {
                    terminal_put(x, y, (*it)->character);
                }
            }
        }
        terminal_refresh();
        terminal_clear();
        terminal_delay(20);
    }

    terminal_close();
}
