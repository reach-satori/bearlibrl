#include "tile.h"
#include "globals.h"

Tile::Tile(TILE_TAG tag) : tag(tag) {};

const std::map<TILE_TAG, uint> Tile::basechars = {
    {T_FLOOR, 0x2E},
    {T_WALL, 0x23},
    {T_AIR, 0x2193},
    {T_RAMP, 0x25CA}
};

void Tile::set_visible() {
    visible = true;
    seen = true;
}

void Tile::draw(uint x, uint y) {
    if (!visible) {
        if (!seen) {
            terminal_put(x, y, 0x20);
        } else {
            terminal_color(0xff191919);
            terminal_put(x, y, basechars.find(tag)->second);
            terminal_color(0xffffffff);
        }
    } else {
        switch (tag) {
            case T_AIR:
                terminal_color(0xff00ff00);
                terminal_put(x, y, basechars.find(tag)->second);
                terminal_color(0xffffffff);
                break;

            default:
                terminal_put(x, y, basechars.find(tag)->second);
                break;
        }
    }
}
