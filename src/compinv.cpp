#include "compinv.h"

Inventorial::Inventorial(float maxweight) : BaseComponent(C_INV), maxweight(maxweight) {}
Inventorial::Inventorial(float maxweight, COMPONENT_TAG tag) : BaseComponent(tag), maxweight(maxweight) {}
Inventorial::Inventorial(void) : Inventorial(50.f) {}

//THIS FUNCTION TAKES OWNERSHIP OF ITEM
int Inventorial::add_to_inventory(std::shared_ptr<Entity>& item) {
    auto pupptr = item->get_component<Carrial>(C_CARR);
    if (pupptr == nullptr)
        return -1; // means the entity on which pickup was attempted has no Carrial component, early return
    if (pupptr->weight + currload > maxweight)
        return -2; // over max weight
    if ( pupptr->invptr.lock() == parent.lock() )
        return -3; // already in THIS inventory
    if (!pupptr->invptr.expired())
        return -4; // already in an inventory

    //items inside an inventory hold a weak pointer to the entity whose inventory they're in
    pupptr->invptr = parent;
    currload += pupptr->weight;
    inventory.insert(item);
    return 0;
}

int Inventorial::remove_from_inventory(std::shared_ptr<Entity>& item) {
    auto droptr = item->get_component<Carrial>(C_CARR);
    if (droptr == nullptr)
        return -1; // means the entity on which drop was attempted has no Carrial component, early return
    if (droptr->invptr.expired())
        return -2; // entity not in an inventory to be removed from
    if (droptr->invptr.lock() != parent.lock()) {
        return -3; // entity is in an inventory, but not this one
    }

    inventory.erase(item);
    currload -= droptr->weight;
    droptr->invptr = std::weak_ptr<Entity>();
    return 0;
}

void Inventorial::refresh_weight() {
    float out = 0;
    for (const auto& it : inventory) {
        auto comp = it->get_component<Carrial>(C_CARR);
        assert(comp != nullptr);
        out += comp->weight;
    }
    currload = out;
}


///////////////////////

int EquipInventorial::inner_equip_item(std::shared_ptr<Entity>& equipped) {
    auto eqpptr = equipped->get_component<EquipCarrial>(C_CARR_EQUIP);
    auto eqslot = eqpptr->slot;
    auto matchingslots = slotlist.find(eqslot);
    if (eqpptr == nullptr)
        return -1; //tried to equip an unequippable entity
    if (matchingslots == slotlist.end())
        return -2; // you don't have appropriate limbs to wear the item
    if (equipped->get_component<Carrial>(C_CARR_EQUIP)->parent.lock() != parent.lock())
        return -3; // equipped item is not in the owner's inventory
    auto eqrange = slotlist.equal_range(eqslot);
    std::multimap<EQUIP_SLOT_TAG, bool>::iterator it;
    for (it = eqrange.first; it != eqrange.second; it++ ) {
        if (!it->second) break;
    }
    if (it == eqrange.second)
        return -4; // no free slots of the correct type

    return 0;

}
