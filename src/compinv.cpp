#include "compinv.h"

Inventorial::Inventorial(float maxweight) : BaseComponent(C_INV), maxweight(maxweight) {}
Inventorial::Inventorial(void) : Inventorial(50.f) {}

int Inventorial::add_to_inventory(std::shared_ptr<Entity> item) {
    std::shared_ptr<Carrial> pupptr = std::dynamic_pointer_cast<Carrial>(item->search_tags_for(C_CARR));
    if (pupptr == nullptr)
        return -1; // means the entity on which pickup was attempted has no Carrial component, early return

    if (pupptr->weight + currload > maxweight)
        return -2; // over max weight

    if (pupptr->invptr != nullptr)
        return -3; // already in an inventory

    //items inside an inventory hold (non-owning) raw pointer to the inventorial component they're in
    //weak pointers are apparently too much trouble
    pupptr->invptr = this;
    inventory.insert(item);
    return 0;
}

int Inventorial::remove_from_inventory(std::shared_ptr<Entity> item) {
    std::shared_ptr<Carrial> pupptr = std::dynamic_pointer_cast<Carrial>(item->search_tags_for(C_CARR));
    if (pupptr == nullptr)
        return -1; // means the entity on which drop was attempted has no Carrial component, early return
    if (pupptr->invptr == nullptr)
        return -2; // entity not in an inventory to be removed from
    if (pupptr->invptr != this) {
        return -3; // entity is in an inventory, but not this one
    }

    pupptr->invptr = nullptr;
    assert(inventory.find(item) != inventory.end());
    inventory.erase(item);
    return 0;
}
