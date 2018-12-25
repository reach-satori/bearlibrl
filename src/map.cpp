#include <map>
#include "map.h"
#include "globals.h"
#include "util.h"



//constructor just makes a solid wall map of widthxheight
//widthxheight map, each 'tile' is really a map of tiletag:tile* (pointers to just one immutable tile instance per tile
Map::Map(uint width, uint height) : width(width), height(height) {
    std::map<uint, Tile*> outermost{std::make_pair(T_WALL, get_tile_ptr(T_WALL))};
    std::vector<std::map<uint, Tile*>> col(height, outermost);
    tiles = std::vector<std::vector<std::map<uint, Tile*>>>(width, col);
};

Map::Map() : Map::Map(80, 25) {};

std::vector<uint> Map::get_tags(uint x, uint y) {
    std::vector<uint> out;
    for (auto const& pair: tiles[x][y]) {
        out.push_back(pair.first);
    }
    return out;
}

bool Map::is_passable(uint x, uint y) {
    x = clamp(x, 0, width-1);
    y = clamp(y, 0, height-1);

    auto tags = get_tags(x, y);
    for (auto const& tag:  tags) {
        Tile *tile = get_tile_ptr(tag);
        if (tile->passable) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

void create_room(Map* map, uint xi, uint yi, uint w, uint h) {
    for (uint x = xi; x < xi + w; x++) {
        for (uint y = yi; y < yi + h; y++) {
            map->tiles[x][y] = std::map<uint, Tile*>{std::make_pair(T_FLOOR, get_tile_ptr(T_FLOOR))};
        }
    }
}

Tile* get_tile_ptr(uint tag) {
    return alltiles.find(tag)->second;
}



