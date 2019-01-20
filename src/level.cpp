#include "globals.h"
#include "level.h"


constexpr int Level::multipliers[4][8];

const static std::vector<int> dirs{
    -1, -1,
    -1,  0,
    -1,  1,
     0, -1,
     0,  0,
     0,  1,
     1, -1,
     1,  0,
     1,  1
};


//constructor just makes a solid wall map of widthxheight
//widthxheight map, each 'tile' is really a map of tiletag:tile* (pointers to just one immutable tile instance per tile
Level::Level(uint depth, uint width, uint height) : width(width), height(height), depth(depth) {
    Tile outermost = Tile(T_WALL);
    std::vector<Tile> col(height, outermost);
    auto t = std::vector<std::vector<Tile>>(width, col);
    for (uint i=0; i<depth; i++){
        tiles.push_back(t);
    }
};

Level::Level() : Level::Level(1, 80, 25) {};

bool Level::is_visible(uint f, uint x, uint y) const {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return false;
    return tiles[f][x][y].visible;
}

bool Level::passable(uint f, uint x, uint y) const {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return false;
    return pass.find(tiles[f][x][y].tag)->second;
}

bool Level::blocks_vision(uint f, uint x, uint y) {
    return vblock.find(tiles[f][x][y].tag)->second;
}

Tile* Level::at(uint f, uint x, uint y) {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return nullptr;
    return &tiles[f][x][y];
}

void Level::set_square_visible(uint f, uint x, uint y) {
    for (uint i = 0; i < dirs.size(); i += 2) {
        auto t = at(f, x+dirs[i], y+dirs[i+1]);
        if (t) {
            t->set_visible();
        }
    }
}

void Level::randomize() {
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height ; y++) {
            for (uint f = 0; f < depth ; f++) {
                if (rand() % 10 == 1) tiles[f][x][y] = Tile(T_WALL); else tiles[f][x][y] = Tile(T_FLOOR);
            }
        }
    }
}

const std::map<TILE_TAG, bool> Level::pass = {
    {T_FLOOR, true},
    {T_WALL, false},
    {T_AIR, false},
    {T_RAMP, true}
};
const std::map<TILE_TAG, bool> Level::vblock = {
    {T_FLOOR, false},
    {T_WALL, true},
    {T_AIR, false},
    {T_RAMP, false}
};

void Level::create_room(uint f, uint xi, uint yi, uint w, uint h, TILE_TAG ttag) {
    for (uint x = xi; x < xi + w; x++) {
        for (uint y = yi; y < yi + h; y++) {
            tiles[f][x][y] = Tile(ttag);
        }
    }
}

//copypasted wholesale from
//http://www.roguebasin.com/index.php?title=C%2B%2B_shadowcasting_implementation
//fov algorithm by mr bjorn bergstrom
void Level::cast_light(uint f, uint x, uint y, uint radius, uint row,
        float start_slope, float end_slope, uint xx, uint xy, uint yx,
        uint yy) {
    if (start_slope < end_slope) {
        return;
    }
    float next_start_slope = start_slope;
    for (uint i = row; i <= radius; i++) {
        bool blocked = false;
        for (int dx = -i, dy = -i; dx <= 0; dx++) {
            float l_slope = (dx - 0.5) / (dy + 0.5);
            float r_slope = (dx + 0.5) / (dy - 0.5);
            if (start_slope < r_slope) {
                continue;
            } else if (end_slope > l_slope) {
                break;
            }

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;
            if ((sax < 0 && (uint)std::abs(sax) > x) ||
                    (say < 0 && (uint)std::abs(say) > y)) {
                continue;
            }
            uint ax = x + sax;
            uint ay = y + say;
            if (ax >= width || ay >= height) {
                continue;
            }

            uint radius2 = radius * radius;
            if ((uint)(dx * dx + dy * dy) < radius2) {
                auto t = at(f, ax, ay);
                t->set_visible();
                if (t->tag == T_AIR && f > 0) {
                    set_square_visible(f-1, ax, ay);
                }
                if (f < depth-1 && at(f+1, ax, ay)->tag == T_AIR) {
                    set_square_visible(f+1, ax, ay);
                }
            }

            if (blocked) {
                if (blocks_vision(f, ax, ay)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (blocks_vision(f, ax, ay)) {
                blocked = true;
                next_start_slope = r_slope;
                cast_light(f, x, y, radius, i + 1, start_slope, l_slope, xx, xy, yx, yy);
            }
        }
        if (blocked) {
            break;
        }
    }
}

void Level::do_fov(uint f, uint x, uint y, uint radius) {
    for (uint i = 0; i < 8; i++) {
        cast_light(f, x, y, radius, 1, 1.0, 0.0, multipliers[0][i],
                multipliers[1][i], multipliers[2][i], multipliers[3][i]);
    }
}

void Level::all_nonvisible() {
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height ; y++) {
            for (uint f = 0; f < depth ; f++) {
                tiles[f][x][y].visible = false;
            }
        }
    }
}

std::set<std::shared_ptr<Entity>> Level::get_entities_in_spot(uint f, uint x, uint y) const {
    auto out = std::set<std::shared_ptr<Entity>>();
    for (auto& ent : tiles[f][x][y].ents) {
        if (ent->get_component<Positional>(C_POSITIONAL) != nullptr){
            out.insert(ent);
        }
    }
    return out;
}


