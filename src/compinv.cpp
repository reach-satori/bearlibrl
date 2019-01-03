#include "compinv.h"

Inventorial::Inventorial(float maxweight) : BaseComponent(C_INV), maxweight(maxweight) {}
Inventorial::Inventorial(float maxweight, COMPONENT_TAG tag) : BaseComponent(tag), maxweight(maxweight) {}
Inventorial::Inventorial(void) : Inventorial(50.f) {}

//THIS FUNCTION TAKES OWNERSHIP OF ITEM
int Inventorial::add_to_inventory(std::shared_ptr<Entity>& item) {
    auto check = inv_add_check(item);
    if (check == 0) {
        auto pupptr = item->get_component<Carrial>(C_CARR);
        //items inside an inventory hold a weak pointer to the entity whose inventory they're in
        pupptr->invptr = parent;
        currload += pupptr->weight;
        inventory.insert(item);
        item->get_component<Positional>(C_POSITIONAL)->ghost();
    }
    return check;
}

//redundant checks
int Inventorial::inv_add_check(std::shared_ptr<Entity> const & item) const {
    if (!item)
        return -5;
    auto pupptr = item->get_component<Carrial>(C_CARR);
    if (!pupptr)
        return -1; // means the entity on which pickup was attempted has no Carrial component, early return
    if (pupptr->weight + currload > maxweight)
        return -2; // over max weight
    if ( pupptr->invptr.lock() == parent.lock() )
        return -3; // already in THIS inventory
    if (!pupptr->invptr.expired())
        return -4; // already in an inventory
    return 0;
}

int Inventorial::remove_from_inventory(std::shared_ptr<Entity>& item) {
    if (!item)
        return -5;
    auto droptr = item->get_component<Carrial>(C_CARR);
    if (!droptr)
        return -1; // means the entity on which drop was attempted has no Carrial component, early return
    if (droptr->invptr.expired())
        return -2; // entity not in an inventory to be removed from
    if (droptr->invptr.lock() != parent.lock())
        return -3; // entity is in an inventory, but not this one

    item->unghost(C_POSITIONAL);
    auto ownpos = parent.lock()->get_component<Positional>(C_POSITIONAL);
    assert(ownpos != nullptr && "for now, nothing without a positional component should be able to drop items\n");
    item->get_component<Positional>(C_POSITIONAL)->setpos(ownpos->x(), ownpos->y());
    inventory.erase(item);
    currload -= droptr->weight;
    droptr->invptr = std::weak_ptr<Entity>();
    return 0;
}

std::vector<std::shared_ptr<Entity>> Inventorial::inv_to_vector() const {
    return std::vector<std::shared_ptr<Entity>>(inventory.begin(), inventory.end());
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
    if (!equipped)
        return -5;
    auto eqpptr = equipped->get_component<EquipCarrial>(C_CARR_EQUIP);
    auto eqslot = eqpptr->slot;
    auto matchingslots = slotlist.find(eqslot);
    if (!eqpptr)
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

