#include "globals.h"
#include "level.h"


constexpr int Level::multipliers[4][8];

//constructor just makes a solid wall map of widthxheight
//widthxheight map, each 'tile' is really a map of tiletag:tile* (pointers to just one immutable tile instance per tile
Level::Level(uint depth, uint width, uint height) : width(width), height(height), depth(depth) {
    Tile outermost = WallTile();
    std::vector<Tile> col(height, outermost);
    auto t = std::vector<std::vector<Tile>>(width, col);
    for (int i=0; i<depth; i++){
        tiles.push_back(t);
    }
};

Level::Level() : Level::Level(1, 80, 25) {};

bool Level::is_visible(uint f, uint x, uint y) const {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return false;
    return tiles[f][x][y].visible;
}

uint Level::get_character(uint f, uint x, uint y) const {
    return tiles[f][x][y].character();
}

bool Level::is_passable(uint f, uint x, uint y) const {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return false;
    return tiles[f][x][y].passable();
}

Tile* Level::at(uint f, uint x, uint y) {
    if (x < 0  || x >= width || y < 0 || y >= height || f < 0 || f >= depth ) return nullptr;
    return &tiles[f][x][y];
}

void Level::randomize() {
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height ; y++) {
            for (uint f = 0; f < depth ; f++) {
                if (rand() % 10 == 1) tiles[f][x][y] = WallTile(); else tiles[f][x][y] = FloorTile();
            }
        }
    }
}


void Level::create_room(uint f, uint xi, uint yi, uint w, uint h) {
    for (uint x = xi; x < xi + w; x++) {
        for (uint y = yi; y < yi + h; y++) {
            tiles[f][x][y] = FloorTile();
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
                tiles[f][ax][ay].visible = true;
            }

            if (blocked) {
                if (!is_passable(f, ax, ay)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (!is_passable(f, ax, ay)) {
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


