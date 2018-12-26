#include "invcomp.h"

Inventorial::Inventorial(float maxweight) : BaseComponent(C_INV), maxweight(maxweight) {}
Inventorial::Inventorial(void) : Inventorial(50.f) {}

void Inventorial::pickup(std::shared_ptr<Entity> picked_up) {
    std::shared_ptr<Carrial> pupptr = std::dynamic_pointer_cast<Carrial>(picked_up->search_tags_for(C_CARR));
    if (pupptr == nullptr)
        return; // means the entity on which pickup was attempted has no Carrial component

    std::shared_ptr<Inventorial> out = std::shared_ptr<Inventorial>(this);

    //items inside an inventory hold a weak pointer to the inventorial component they're in
    pupptr->invptr = std::weak_ptr<Inventorial>(out);
    inventory.push_back(picked_up);
}
