#include <map>
#include <vector>
#include <tile.h>


struct Map {
    unsigned int width;
    unsigned int height;
    std::vector<std::vector<std::vector<Tile*>>> tiles;
};
