#include "draw.h"

void draw_map(Map map) {
    for (uint x = 0; x < map.width; x++) {
        for (uint y = 0; y < map.height; y++) {
            for (auto it = map.tiles[x][y].begin(); it != map.tiles[x][y].end(); it++) {
                terminal_put(x, y, (*it).second->character);
            }
        }
    }
}

void draw_entities(std::set<std::shared_ptr<Entity>> entities) {
    for (auto const& ent : entities) {
        auto tags = ent->get_tags();
        auto pos = tags.find(C_POSITIONAL);
        if (pos == tags.end()) {
            return; //no positional, no draw
        } else {
            //cast shr_ptr BaseComponent to shr_ptr Positional
            auto positional = std::dynamic_pointer_cast<Positional>(ent->components.find(*pos)->second);
            auto realpos = positional->pos;
            terminal_put(realpos[0], realpos[1], positional->codepoint);
        }
    }
}
