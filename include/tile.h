#pragma once
#include "tiletags.h"
#include "typedefs.h"
#include <vector>

struct Tile {

    uint tag = 0;
    uint character;

    Tile(uint tag, uint character);
};


struct FloorTile: public Tile {
    bool passable = true;
    FloorTile();
};

struct WallTile: public Tile {
    bool passable = false;
    WallTile();
};
