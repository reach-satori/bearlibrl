#include "events.h"
#include "globals.h"

void move(Entity * ent, int x, int y) {
    auto pos = ent->get_component<Positional>(C_POSITIONAL);
    if (pos == nullptr) {
        printf("Entity with no positional component attempted to move\n");
        return;
    }
    if (levelmanager->get_const_currlvl().is_passable(x, y)){
        pos->pos[0] = x;
        pos->pos[1] = y;
    }
}

void item_pickup(Entity* carrier, std::shared_ptr<Entity>& item) {
    auto inv = carrier->get_component<Inventorial>(C_INV);
    if (inv == nullptr) {
        printf("Entity with no inventory component attempted to pick an item up\n");
        return;
    }
    switch(inv->add_to_inventory(item)) {
        case -1:
            printf("Something attempted to pick up a non-item\n");
            break;
        case -2:
            printf("Attempted to pick up an item over max weight\n");
            break;
        case -3:
            printf("Attempted to pick up an item already in this inventory\n");
            break;
        case -4:
            printf("Attempted to pick up an item already in another inventory\n");
            break;
        case 0:
            printf("picked up\n");
            break;
    }
}

