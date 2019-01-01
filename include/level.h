#pragma once
#include <map>
#include <vector>
#include <memory>
#include <cstdlib>
#include <tile.h>
#include "util.h"
#include "fdecs.h"
#include "comptags.h"
#include "entity.h"


struct Level {
    uint width;
    uint height;
    std::vector<std::vector<Tile>> tiles;

    static int constexpr multipliers[4][8] = {
        {1, 0, 0, -1, -1, 0, 0, 1},
        {0, 1, -1, 0, 0, -1, 1, 0},
        {0, 1, 1, 0, 0, -1, -1, 0},
        {1, 0, 0, 1, -1, 0, 0, -1}
    };

    Level();
    Level(uint width, uint height);
    void create_room(uint xi, uint yi, uint w, uint h);
    void cast_light( uint x, uint y, uint radius, uint row,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy);
    void do_fov(uint x, uint y, uint radius);
    void randomize();
    void all_nonvisible();
    bool is_passable(uint x, uint y) const;
    bool is_visible(uint x, uint y) const;
    uint get_character(uint x, uint y) const;

    std::set<std::shared_ptr<Entity>> get_entities_in_spot(int, int) const;

    template <typename T>
    std::vector<T*> get_components_in_spot(int x, int y, COMPONENT_TAG tag) const {
        std::vector<T*> out;
        for (auto const& et : get_entities_in_spot(x, y)) {
            T* comp = et->get_component<T>(tag);
            if (comp != nullptr) out.push_back(comp);
        }
        return out;
    }
};
