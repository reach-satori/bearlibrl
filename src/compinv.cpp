#include "compinv.h"

Inventorial::Inventorial(float maxweight) : BaseComponent(C_INV, C_EMPTY), maxweight(maxweight) {}
Inventorial::Inventorial(void) : Inventorial(50.f) {}

//THIS FUNCTION TAKES OWNERSHIP OF ITEM
int Inventorial::add_to_inventory(std::shared_ptr<Entity> item) {
    Carrial *pupptr = dynamic_cast<Carrial*>(item->get_change_component(C_CARR));
    if (pupptr == nullptr)
        return -1; // means the entity on which pickup was attempted has no Carrial component, early return
    if (pupptr->weight + currload > maxweight)
        return -2; // over max weight
    if (pupptr->invptr.lock().get() == parent.lock().get())
        return -3; // already in THIS inventory
    if (!pupptr->invptr.expired())
        return -4; // already in an inventory

    //items inside an inventory hold a weak pointer to the entity whose inventory they're in
    pupptr->invptr = parent;
    inventory.insert(item);
    return 0;
}

int Inventorial::remove_from_inventory(std::shared_ptr<Entity> item) {
    auto pupptr = std::shared_ptr<Carrial>(dynamic_cast<Carrial*>(item->get_change_component(C_CARR)));
    if (pupptr == nullptr)
        return -1; // means the entity on which drop was attempted has no Carrial component, early return
    if (pupptr->invptr.expired())
        return -2; // entity not in an inventory to be removed from
    if (pupptr->invptr.lock() != parent.lock()) {
        return -3; // entity is in an inventory, but not this one
    }

    inventory.erase(pupptr->invptr.lock());
    pupptr->invptr = std::weak_ptr<Entity>();
    return 0;
}
