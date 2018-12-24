#pragma once
#include "tiletags.h"

struct Tile {

    unsigned int tag = 0;
    unsigned int character;
};


struct FloorTile: public Tile {
    bool passable = true;
    FloorTile() {
        character = 0x2e;
        tag = T_FLOOR;
    }
};
struct WallTile: public Tile {
    bool passable = false;
    WallTile() {
        character = 0x23;
        tag = T_WALL;
    }
};
