#include "globals.h"
#include "level.h"



//constructor just makes a solid wall map of widthxheight
//widthxheight map, each 'tile' is really a map of tiletag:tile* (pointers to just one immutable tile instance per tile
Level::Level(uint width, uint height) : width(width), height(height) {
    std::pair<uint, Tile*> outermost = std::make_pair(T_WALL, get_tile_ptr(T_WALL));
    std::vector<std::pair<uint, Tile*>> col(height, outermost);
    tiles = std::vector<std::vector<std::pair<uint, Tile*>>>(width, col);
};

Level::Level() : Level::Level(80, 25) {};

bool Level::is_passable(uint x, uint y) {
    bool out = true;
    if (x <= 0 || x >= width || y <= 0 || y >= height)
        out = false;

    if (!tiles[x][y].second->passable)
        out = false;

    return out;
}

void Level::create_room(uint xi, uint yi, uint w, uint h) {
    for (uint x = xi; x < xi + w; x++) {
        for (uint y = yi; y < yi + h; y++) {
            tiles[x][y] = std::make_pair(T_FLOOR, get_tile_ptr(T_FLOOR));
        }
    }
}

Tile* get_tile_ptr(uint tag) {
    return alltiles.find(tag)->second;
}



