#pragma once
#include <map>
#include <vector>
#include <memory>
#include <cstdlib>
#include <tile.h>

#include "noise.h"

#include "util.h"
#include "fdecs.h"
#include "comptags.h"
#include "entity.h"


struct Level {
    uint width;
    uint height;
    uint depth;
    std::vector<std::vector<std::vector<Tile>>> tiles;

    static int constexpr multipliers[4][8] = {
        {1, 0, 0, -1, -1, 0, 0, 1},
        {0, 1, -1, 0, 0, -1, 1, 0},
        {0, 1, 1, 0, 0, -1, -1, 0},
        {1, 0, 0, 1, -1, 0, 0, -1}
    };
    static const std::map<TILE_TAG, uint> chars;
    static const std::map<TILE_TAG, bool> pass;
    static const std::map<TILE_TAG, bool> vblock;

    Level();
    Level(uint, uint, uint);
    void create_room(uint, uint, uint, uint, uint, TILE_TAG);
    void cast_light(uint f, uint x, uint y, uint radius, uint row,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy);
    void do_fov(uint, uint, uint, uint);
    bool blocks_vision(uint, uint, uint);
    void randomize();
    void all_nonvisible();
    void all_visible();
    void set_square_visible(uint, uint, uint);
    bool is_visible(uint, uint, uint) const;
    bool blocks_vision(uint, uint, uint) const;
    bool passable(uint, uint, uint) const;
    Tile* at(uint, uint, uint);

    std::set<std::shared_ptr<Entity>> get_entities_in_spot(uint, uint, uint) const;

    template <typename T>
    std::vector<T*> get_components_in_spot(uint f, uint x, uint y, COMPONENT_TAG tag) const {
        std::vector<T*> out;
        for (auto const& et : get_entities_in_spot(f, x, y)) {
            T* comp = et->get_component<T>(tag);
            if (comp != nullptr) out.push_back(comp);
        }
        return out;
    }
};

void lvlgen(Level*);

