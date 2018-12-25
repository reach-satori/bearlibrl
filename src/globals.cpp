#include "globals.h"

std::map<uint, Tile*> alltiles {
    std::make_pair(T_FLOOR, new FloorTile),
    std::make_pair(T_WALL, new WallTile)
};
