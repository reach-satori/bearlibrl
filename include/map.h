#pragma once
#include <map>
#include <vector>
#include <tile.h>


struct Map {
    uint width;
    uint height;
    std::vector<std::vector<std::map<uint, Tile*>>> tiles;

    Map();
    Map(uint width, uint height);
    std::vector<uint> get_tags(uint x, uint y);
};

void create_room(Map* map, uint xi, uint yi, uint w, uint h);
Tile* get_tile_ptr(uint tag);
