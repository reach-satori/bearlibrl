#include "map.h"



Map::Map(uint width, uint height) : width(width), height(height) {};
Map::Map() : width(80), height(25) {};

std::vector<uint> Map::get_tags(uint x, uint y) {
    std::vector<uint> out;
    for (auto const& pair: tiles[x][y]) {
        out.push_back(pair.first);
    }
    return out;
}




