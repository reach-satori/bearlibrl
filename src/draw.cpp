#include "draw.h"

void draw_map(std::shared_ptr<Map> map) {
    for (uint x = 0; x < map->width; x++) {
        for (uint y = 0; y < map->height; y++) {
            for (auto it = map->tiles[x][y].begin(); it != map->tiles[x][y].end(); it++) {
                terminal_put(x, y, (*it).second->character);
            }
        }
    }
}

void draw_entities(std::shared_ptr<std::set<std::shared_ptr<Entity>>> entities) {
    if (entities->size() == 0) return;

    for (auto const& ent : *entities) {
        auto pos = ent->get_positional(); // maybe add a "visual" component instead later
        if (pos == nullptr) continue;
        pos->draw();
    }
}

