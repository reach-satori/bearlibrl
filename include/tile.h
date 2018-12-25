#pragma once
#include "tiletags.h"
#include "typedefs.h"
#include <vector>
#include <map>

struct Tile {

    uint tag = 0;
    uint character;
    uint passable;

    Tile(uint tag, uint character, bool passable);
};


struct FloorTile: public Tile {
    FloorTile();
};

struct WallTile: public Tile {
    bool passable = false;
    WallTile();
};

