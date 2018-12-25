#include "entity.h"
#include "typedefs.h"
#include <map>

void Entity::add_component(BCptr comp) {
    //parent is weak_ptr
    comp->parent = std::make_shared<Entity>(*this);
    //add component
    auto compin = std::make_pair(comp->tag, comp);
    components.insert(compin);
    //add tag to taglist
    //add parent weak_ptr to component "parent" field
}

std::set<uint> Entity::get_tags(void)  {
    std::set<uint> out;
    if (components.size() == 0) {
        out.insert(0);
        return out;
    }
    for (auto it = components.begin(); it != components.end(); it++) {
        out.insert(it->first);
    }
    return out;
}
