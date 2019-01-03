#include "tile.h"

Tile::Tile(TILE_TAG tag) : tag(tag) {};

FloorTile::FloorTile() : Tile(T_FLOOR) {};
WallTile::WallTile() : Tile(T_WALL) {};

bool Tile::passable() const {
    bool out;
    switch(tag) {
        case T_FLOOR:
            out = true;
            break;
        case T_WALL:
            out = false;
            break;
    }
    return out;
}

uint Tile::character() const {
    uint out;
    switch(tag) {
        case T_FLOOR:
            out = 0x2E;
            break;
        case T_WALL:
            out = 0x23;
            break;
    }
    return out;
}

