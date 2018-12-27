#pragma once
#include "typedefs.h"
#include "tiletags.h"
#include <vector>
#include <map>

struct Tile {

    TILE_TAG tag = T_FLOOR;
    uint character;
    uint passable;

    Tile(TILE_TAG tag, uint character, bool passable);
};


struct FloorTile: public Tile {
    FloorTile();
};

struct WallTile: public Tile {
    bool passable = false;
    WallTile();
};

