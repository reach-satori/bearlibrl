#include "tile.h"

Tile::Tile(uint tag, uint character) : tag(tag), character(character) {};

FloorTile::FloorTile() : Tile(T_FLOOR, 0x2e) {};
WallTile::WallTile() : Tile(T_WALL, 0x23) {};
