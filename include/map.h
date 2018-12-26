#pragma once
#include <map>
#include <vector>
#include <tile.h>
#include "util.h"


struct Map {
    uint width;
    uint height;
    std::vector<std::vector<std::pair<uint, Tile*>>> tiles;

    Map();
    Map(uint width, uint height);
    bool is_passable(uint x, uint y);
};

void create_room(Map* map, uint xi, uint yi, uint w, uint h);
Tile* get_tile_ptr(uint tag);
