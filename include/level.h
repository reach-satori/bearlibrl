#pragma once
#include <map>
#include <vector>
#include <memory>
#include <tile.h>
#include "util.h"
#include "fdecs.h"


struct Level {
    uint width;
    uint height;
    std::vector<std::vector<std::pair<uint, Tile>>> tiles;

    static int constexpr multipliers[4][8] = {
        {1, 0, 0, -1, -1, 0, 0, 1},
        {0, 1, -1, 0, 0, -1, 1, 0},
        {0, 1, 1, 0, 0, -1, -1, 0},
        {1, 0, 0, 1, -1, 0, 0, -1}
    };

    Level();
    Level(uint width, uint height);
    bool is_passable(uint x, uint y) const;
    void create_room(uint xi, uint yi, uint w, uint h);
    void cast_light( uint x, uint y, uint radius, uint row,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy);
    void do_fov(uint x, uint y, uint radius);
    void all_nonvisible();
    bool is_visible(uint x, uint y);
    uint get_character(uint x, uint y);
    std::vector<std::shared_ptr<Entity>> get_entities_in_spot(int, int) const;
};
