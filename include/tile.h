#pragma once
#include "typedefs.h"
#include "tiletags.h"
#include <set>
#include <memory>
#include "fdecs.h"

struct Tile {
    TILE_TAG tag = T_FLOOR;
    bool visible = false;
    std::set<std::shared_ptr<Entity>> ents;
    bool passable() const;
    uint character() const;

    Tile(TILE_TAG tag);
};


struct FloorTile: public Tile {
    FloorTile();
};

struct WallTile: public Tile {
    WallTile();
};

