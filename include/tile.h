#pragma once
#include "typedefs.h"
#include "tiletags.h"
#include "fdecs.h"
#include "BearLibTerminal.h"
#include <set>
#include <map>
#include <memory>

struct Tile {
    TILE_TAG tag = T_FLOOR;
    bool visible = false;
    bool seen = false;
    std::set<std::shared_ptr<Entity>> ents;
    const static std::map<TILE_TAG, uint> basechars;

    Tile(TILE_TAG tag);
    void draw(uint, uint);
    void set_visible();
    void set_surroudings_visible();
};
