#include "BearLibTerminal.h"
#include <stdio.h>
#include "map.h"
#include "tile.h"
#include "entity.h"
#include "poscomp.h"
#include "comptags.h"
#include "typedefs.h"

FloorTile *flor = new FloorTile();
WallTile *wall = new WallTile();

void create_room(Map* map, uint xi, uint yi, uint w, uint h) {
    for (uint x = xi; x < xi + w; x++) {
        for (uint y = yi; y < yi + h; y++) {
            map->tiles[x][y] = std::map<uint, Tile*>{std::make_pair(T_FLOOR, flor)};
        }
    }
}

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
    Map map;
    map.width=80;
    map.height=25;
    std::map<uint, Tile*> outermost{std::make_pair(T_WALL, wall)};
    std::vector<std::map<uint, Tile*>> col(map.height, outermost);
    map.tiles = std::vector<std::vector<std::map<uint, Tile*>>>(map.width, col);
    //widthxheight map, each 'tile' is really a map of tiletag:tile* (pointers to just one immutable tile instance per tile
    //

    //create a room in the map
    create_room(&map, 10, 10, 10, 10);

    auto player = std::make_shared<Entity>();
    auto pos = std::make_shared<Positional>(13, 13);
    pos->codepoint = 0x40;
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
        for (uint x = 0; x < map.width; x++) {
            for (uint y = 0; y < map.height; y++) {
                for (auto it = map.tiles[x][y].begin(); it != map.tiles[x][y].end(); it++) {
                    terminal_put(x, y, (*it).second->character);
                }
            }
        }


        //draw the player
        for (auto const& tag : player->get_tags()) {
            //do something (or not) for each tag
            //probably this would be moved in the future to a function with a switch case of tags
            if (tag == C_POSITIONAL) {
                //this raw pointer gets nuked right away so it should be ok
                //i didn't find a way to cast to derived class pointer with shared_ptr
                auto positional = (Positional*)player->components.find(C_POSITIONAL)->second.get();
                auto& pos = positional->pos;
                while (terminal_has_input()){
                    key = terminal_read();
                }
                switch(key) {
                    case TK_LEFT: pos[0] -= 1; break;
                    case TK_RIGHT: pos[0] += 1; break;
                    case TK_DOWN: pos[1] += 1; break;
                    case TK_UP: pos[1] -= 1; break;
                }
                key = 0;
                terminal_put(pos[0], pos[1], positional->codepoint);
            }
        }

        //draw entities
        terminal_refresh();
        terminal_clear();
        terminal_delay(20);
    }

    terminal_close();
}
