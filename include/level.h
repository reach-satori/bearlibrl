#pragma once
#include <map>
#include <vector>
#include <tile.h>
#include "util.h"


struct Level {
    uint width;
    uint height;
    std::vector<std::vector<std::pair<uint, Tile*>>> tiles;

    Level();
    Level(uint width, uint height);
    bool is_passable(uint x, uint y);
    void create_room(uint xi, uint yi, uint w, uint h);
};

Tile* get_tile_ptr(uint tag);
