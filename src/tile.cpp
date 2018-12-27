#include "tile.h"

Tile::Tile(TILE_TAG tag, uint character, bool passable) : tag(tag), character(character), passable(passable) {};

FloorTile::FloorTile() : Tile(T_FLOOR, 0x2e, true) {};
WallTile::WallTile() : Tile(T_WALL, 0x23, false) {};
